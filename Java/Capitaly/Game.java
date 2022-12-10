import java.util.List;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;
import java.lang.NumberFormatException;


public class Game {
    
    public List <Player> players;
    public List <Field> fields;
    private File theFile;

    /**
     * @param fileName requires DataFile
     */
    public Game (String fileName) { 

        this.theFile = new File(fileName);  
        this.players = new ArrayList<Player>();
        this.fields = new ArrayList<Field>();
    }


    /**
     * This method takes a player and a result from the dice throw.
     * It moves the player to a certain field and makes the player interact with the field according to their strategy, field type.
     * Player's location automatically gets changed through this function.
     * @param thePlayer
     * @param diceNumber
     */
    public void PlayerPlays (Player thePlayer, int diceNumber) {

        int goToLoc = thePlayer.getBoardLocation() + diceNumber;
        while (goToLoc > this.fields.size()) { goToLoc -= this.fields.size(); }
        
        thePlayer.setBoardLocation(goToLoc);
        Boolean interaction = thePlayer.stepOn(this.fields.get(goToLoc-1));
        thePlayer.doStrategy(interaction, (this.fields.get(goToLoc-1)));
    }


    /**
     * This method must be used right after creating a game instance.
     * This method checks validity of the given fileName. As well as initalizes the values(given that they are correct) and creates objects.
     * @throws FileNotFoundException when the file does not exist
     * @throws NumberFormatException when an int couldn't be parsed
     * @throws IOException when a line in the file is not properly formatted
     */
    public void initalizeGame () throws FileNotFoundException, NumberFormatException, IOException {

        if (!this.theFile.exists()) throw new FileNotFoundException("The file: '"+this.theFile.toString()+"' does not exist!");
        else {
    
            //Reading the Fields
            try {

                Scanner sc = new Scanner (this.theFile);

                int NumOfFields = Integer.parseInt(sc.nextLine());
                if ( NumOfFields % 4 != 0 ) { sc.close(); throw new IOException("Number of fields must be a multiple 4 (Parity game rules). Got: "+NumOfFields); }
                int FieldCounter = 1;
                Boolean flag = true;


                //ReadFields
                while (flag && sc.hasNext()) {
                    String toField = sc.nextLine();

                    //Valid line
                    if(toField.split(" ").length == 2) {

                        String [] splitted = toField.split(" ");
                        if (splitted[0].equals("Lucky")) this.fields.add(new Lucky(Integer.parseInt(splitted[1]),FieldCounter));
                        else if (splitted[0].equals("Service")) this.fields.add(new Service(Integer.parseInt(splitted[1]),FieldCounter));
                        else if (splitted[0].equals("Property")) this.fields.add(new Property(splitted[1],FieldCounter));
                        else { sc.close(); flag = false; throw new NumberFormatException("Couldn't parse line: '"+toField+"' correctly!"); }
                    }
                    //Invalid line
                    else { sc.close(); flag = false; throw new IOException(("Couldn't parse line: '"+toField+"' correctly because it doesn't represent a valid value!")); }


                    FieldCounter++;
                    if (FieldCounter > NumOfFields) { flag = false; }
                }


                int NumOfPlayers = Integer.parseInt(sc.nextLine());
                int PlayerCounter = 1;
                flag = true;


                //Read Players
                while (flag && sc.hasNext()) {

                    String toPlayer = sc.nextLine();
                    if (toPlayer.split(" ").length == 2) {

                        String [] splitted = toPlayer.split(" ");

                        if (splitted[1].equals(Strategy.Greedy.toString())) this.players.add(new Greedy_Player(splitted[0], Strategy.Greedy));
                        else if (splitted[1].equals(Strategy.Careful.toString())) this.players.add(new Careful_Player(splitted[0], Strategy.Careful));
                        else if (splitted[1].equals(Strategy.Tactical.toString())) this.players.add(new Tactical_Player(splitted[0], Strategy.Tactical));
                        else { sc.close(); flag = false; throw new IOException("Couldn't parse: '"+splitted[1]+"' correctly because it is not a strategy!"); }
                    }
                    else { sc.close(); flag = false; throw new IOException("Couldn't parse line: '"+toPlayer+"' correctly because it has an incorrect value!"); }


                    PlayerCounter++;
                    if(PlayerCounter > NumOfPlayers) flag = false;
                }

                sc.close();
            
            } catch (Exception E) { 
                if (E.getClass() == NumberFormatException.class) System.out.println("Couldn't parse an integer correctly!");
                else if (E.getClass() == IOException.class ) System.out.println(E.getMessage());  
                else { System.out.println(E.getMessage()); }
                System.out.println("Exiting program!"); System.exit(1);
            }
        }
    }


    /**
     * Function used inside the: playGame() methods, it returns the amount of players currently playing.
     * Critical to determine winnner.
     * @return amount of players
     */
    private int playersPlaying () {

        int answer = 0;
        for (Player x: players) { if (x.isPlaying) answer++; }
        return answer;
    }


    /**
     * This method prints to the console the winner of the game after using one of the playGame methods.
     */
    private void ReturnWinner () { 
        for (Player x: players) { 
            if (x.isPlaying) {
                System.out.println("\nWinner: "+x.toString()+", Properties: "+x.properties);
                break;
            } 
        }
    }
    
 
    /**
     * Prints the players onto the screen with their stats
     */
    public void DisplayPlayers () { for(Player x: players) System.out.println(x); }
    /**
     * Prints the fields onto the screen with their stats
     */
    public void DisplayFields  () { for(Field x: fields) System.out.println(x); }


    /**
     * This method can be used after using the: "initalize.Game()" method. 
     * This method will play the game according to the dice results from the file.
     * Result is shown after a certain amount of rounds is passed.
     * Ideally, the file lines must be either greater or equal to the given round number. 
     * Also, incase there is a winner before the given round number, the game stops.
     * @param fileName of dice results
     * @param rounds number where you would like the result of objects at
     * @throws NumberFormatException when an int couldn't be parsed in the file
     * @throws FileNotFoundException when the file does not exist
     */
    public void playGameFromFile_untilnumber (String fileName, int rounds) throws NumberFormatException, FileNotFoundException {

        File theFile = new File (fileName);
        if (!theFile.exists()) throw new FileNotFoundException("The file '"+fileName+"' does not exist!");

        else {
            
            try {
                Scanner sc = new Scanner (theFile);

                int iterator = 0;   //This will help looping the players array
                int round_number = 0;

                while (sc.hasNextLine()) {

                    if (round_number == rounds) {

                        System.out.println("After "+(rounds)+" rounds we know this about the players:");
                        for (Player p: players) {

                            System.out.println("\n"+p+"\n**PROPERTIES**");
                            for (Property prp: p.properties) {
                                System.out.println(prp);
                            }
                        }
                        break;
                    }

                    //Winner found
                    if (this.playersPlaying() == 1) {

                        System.out.println("*************** GAME STOPPED! There is a Winner in round: '"+(round_number)+"' ***************");
                        this.ReturnWinner();
                        System.out.println("All players: ");
                        this.DisplayPlayers();
                        break;
                    }

                    
                    //Algorithm
                    int diceNum = sc.nextInt();
                    if (diceNum < 1 || diceNum > 6) { sc.close(); throw new NumberFormatException("That wasn't a number between [1-6]!"); }


                    //Check if the player is playing
                    if ( (players.get(iterator)).isPlaying ) {
                        
                        this.PlayerPlays(players.get(iterator), diceNum);

                        if (!players.get(iterator).isPlaying) { //This is to reset the properties incase the player stops playing
                            for (Property p: players.get(iterator).properties) { p.ResetProperty(); }
                        }
                    }
                    //If the player is not playing, get the next playing player.
                    else {

                        while ( !((players.get(iterator)).isPlaying) ) {
                            
                            iterator ++;
                            //This is to restart the players iteration
                            if (iterator == players.size()) { iterator = 0; };
                        }

                        this.PlayerPlays(players.get(iterator), diceNum);

                        if (!players.get(iterator).isPlaying) { //This is to reset the properties incase the player stops playing
                            for (Property p: players.get(iterator).properties) { p.ResetProperty(); }
                        }
                    }

                    iterator ++;
                    //This is to restart the players iteration
                    if (iterator == players.size()) { iterator = 0; }

                    round_number++;
                }


                sc.close();

            } catch (Exception E) { 

                if(E.getClass() == InputMismatchException.class) { System.out.println("That was not an int!"); }
                else System.out.println(E.getMessage());
                System.out.println("Exiting program!"); System.exit(1);
            }
        }
    }


    /**
     * This method can be used after using the: "initalize.Game()" method. 
     * This method will play the game according to the dice results from the file, then it shows the results each time.
     * Printing stops until a Winner is left!
     * Ideally, the file content must be large inorder to insure that there is a Winner.
     * @param fileName of dice results
     * @throws NumberFormatException when an int couldn't be parsed in the file
     * @throws FileNotFoundException when the file does not exist
     */
    public void playGameFromFile_v2 (String fileName) throws NumberFormatException, FileNotFoundException {

        File theFile = new File (fileName);
        if (!theFile.exists()) throw new FileNotFoundException("The file '"+fileName+"' does not exist!");

        else {
            
            try {
                Scanner sc = new Scanner (theFile);

                int iterator = 0;   //This will help looping the players array
                int round_number = 1;
                while (sc.hasNextLine()) {


                    int diceNum = sc.nextInt();
                    if (diceNum < 1 || diceNum > 6) { sc.close(); throw new NumberFormatException("That wasn't a number between [1-6]!"); }


                    //Check if the player is playing
                    if ( (players.get(iterator)).isPlaying ) {
                        
                        this.PlayerPlays(players.get(iterator), diceNum);

                        if (!players.get(iterator).isPlaying) { //This is to reset the properties incase the player stops playing
                            for (Property p: players.get(iterator).properties) { p.ResetProperty(); }
                        }
                    }
                    //If the player is not playing, get the next playing player.
                    else {

                        while ( !((players.get(iterator)).isPlaying) ) {
                            
                            iterator ++;
                            //This is to restart the players iteration
                            if (iterator == players.size()) { iterator = 0; };
                        }

                        this.PlayerPlays(players.get(iterator), diceNum);

                        if (!players.get(iterator).isPlaying) { //This is to reset the properties incase the player stops playing
                            for (Property p: players.get(iterator).properties) { p.ResetProperty(); }
                        }
                    }


                    //This prints in real time the locations and the status of the players
                    System.out.println("\n*************** ROUND "+(round_number)+" RESULTS ***************\n(Player: "+players.get(iterator).name+") threw (Dice: "+diceNum+"), PLAYERS: \n");
                    DisplayPlayers(); System.out.println("\nFIELDS:\n");
                    DisplayFields();
                    
                    iterator ++;
                    //This is to restart the players iteration
                    if (iterator == players.size()) { iterator = 0; }

                    //Winner found
                    if (this.playersPlaying() == 1) {

                        System.out.println("\n*************** There is a Winner in round number: '"+round_number+"' ***************");
                        this.ReturnWinner();
                        System.out.println("All players: ");
                        this.DisplayPlayers();
                        break;
                    }

                    round_number++;
                }

                sc.close();

            } catch (Exception E) { 

                if(E.getClass() == InputMismatchException.class) { System.out.println("That was not an int!"); }
                else System.out.println(E.getMessage());
                System.out.println("Exiting program!"); System.exit(1);
            }
        }
    }
}