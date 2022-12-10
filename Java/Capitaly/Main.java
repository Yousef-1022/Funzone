public class Main {
    public static void main (String [] args) {
        try {

            System.out.println("Write Filename with data: ");
            String DataFileName = System.console().readLine();

            System.out.println("Write Filename with dice numbers: ");
            String DiceFileName = System.console().readLine();

            //System.out.println("Write number of round to display game stats: ");
            //int NumOfRolls = Integer.parseInt(System.console().readLine());

            Game Parity = new Game (DataFileName);
            Parity.initalizeGame();
            //Parity.playGameFromFile_untilnumber(DiceFileName,NumOfRolls);
            Parity.playGameFromFile_v2(DiceFileName);
        }
        catch (Exception E) { System.out.println(E); }
    }
}
//Please use: playGameFromFile_v2() instead of playGameFromFile_untilnumber() if you would like to see what happened every round
//  javac *.java; java Main

//import java.io.PrintWriter;
//import java.io.File;
// try {
//    PrintWriter pw = new PrintWriter(new File("test_rolls.txt"));
//    for (int i = 1; i<=100; i++) pw.write(String.valueOf((int)Math.floor(Math.random()*6 + 1))+'\n'); pw.close();
//} catch (Exception E) {}