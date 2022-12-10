import java.util.List;
import java.util.ArrayList;

abstract class Player {
    
    public String name;
    protected Strategy strategy;
    protected int money;
    protected Boolean isPlaying;
    protected List <Property> properties;

    protected int onBoardLocation = 1;


    protected Player (String name, Strategy strategy) {

        this.name = name;
        this.strategy = strategy;
        this.money = 10000;
        this.isPlaying = true;
        this.properties = new ArrayList<Property>();
    }


    public int getMoney () { return this.money; }
    public void setMoney (int money) { this.money = money; }


    public int getBoardLocation () { return this.onBoardLocation; }
    public void setBoardLocation (int newLocation) { this.onBoardLocation = newLocation; }


    public void displayProperties () { System.out.println (this.properties); }


    /**
     * This function resets the Player object, and makes all the properties owned with it restarted
     */
    protected void eliminatePlayer () { this.isPlaying = false; for (Property p: this.properties) p.ResetProperty(); this.properties.clear(); }


    /**
     * 
     * @param aField is the field which the player must step on
     * @return A BOOL VALUE WHICH: 'true' means that the Player object interacted with the field.
     * This interaction is either to an occupied Property(Automatic deduction and addition to owner is done), or to a Service/Lucky automatic payment.
     * Or, Returns A BOOL VALUE WHICH: 'false' means that the Player object did not interact with the field. 
     * This no interaction is due to either: No Owner of the property exists / This field is not a Service/Lucky field. This method also eliminates Player 
     * object incase their funds go down below 0
     */
    public Boolean stepOn (Field aField) { 

        if (aField.getClass() == Service.class) { 
            
            this.money -= aField.getCost(); 
            if (this.money < 0) { this.eliminatePlayer(); }
            return true; 
        }

        else if (aField.getClass() == Lucky.class) { this.money += aField.getCost(); return true; }
        else {
            
            //If the owner is not this object, deduct.
            if( ((Property)aField).isOwned() && !((((Property)aField).player.name).equals(this.name)) ) { 
                
                //House deduction
                if(((Property)aField).hasHouse()) {
                    this.money -= (2000);
                    ((Property)aField).player.setMoney(2000+((Property)aField).player.getMoney());
                    if (this.money < 0) { this.eliminatePlayer(); }
                }

                //Normal deduction
                else {
                    this.money -= (500);
                    ((Property)aField).player.setMoney(500+((Property)aField).player.getMoney());
                    if (this.money < 0) { this.eliminatePlayer(); }
                }  

                //Interaction happened  
                return true;        
            }
            //If there is no-owner/object is owner (this will indicate that no interaction happened to the field)
            else return false;
        }  
    }


    //This must be used with the main function stepOn to indicate whether an interaction happened or not.
    /**
     * This function must be used right after the function: stepOn(aField). It also modifies the values of the Player according to their strategy
     * @param interact_happend Result of the: stepOn (aField)
     * @param aField Same value used with: stepOn(aField)
     */
    public abstract void doStrategy (Boolean interact_happend, Field aField);
}


class Greedy_Player extends Player {

    public Greedy_Player (String name, Strategy strategy) {
        super (name,strategy);
    }

    
    @Override
    public void doStrategy (Boolean interact_happened, Field aField) {

        //No interaction means either owned/not owned
        if (!interact_happened) {

           //Owned by thisPlayer means they can buy a house on it
            if ( ((Property)aField).isOwned() && (((Property)aField).player.name).equals(this.name) ) {


                ((Property)aField).increaseStep();

                if ( !(((Property)aField).hasHouse()) && (this.money > 4000)) {
                    ((Property)aField).makeHouse();
                    this.money -= 4000;
                }
            }
            //Unowned by this player
            else {
                if(this.money > 1000) {
                    ((Property)aField).makeOwned(this);
                    this.properties.add((Property)aField);
                    this.money -= 1000;
                }
            }
        }
        //Interaction happened, no need to do anything further
        else return;
    }


    @Override
        public String toString () { return "Player name: '"+this.name+"', money: '"+this.money+"', isPlaying? "+this.isPlaying+", CurrentLocation: "+this.onBoardLocation+" , type: "+this.strategy.toString()+" , Properties: "+this.properties.size(); }
}


class Careful_Player extends Player {

    public Careful_Player (String name, Strategy strategy) {
        super (name,strategy);
    }

    @Override
    public void doStrategy (Boolean interact_happened, Field aField) {
       
    //No interaction means either owned/not owned
    if (!interact_happened) {

        //Owned by thisPlayer means that they can buy a house on it
        if ( ((Property)aField).isOwned() && (((Property)aField).player.name).equals(this.name) ) {

            ((Property)aField).increaseStep();

            if ( !(((Property)aField).hasHouse()) && ( (this.money-4000)>=(this.money/2) )) { //At most half of money
                ((Property)aField).makeHouse();
                this.money -= 4000;
            }
        }

        //Unowned by this player
        else {

            if((this.money-1000)>=(this.money/2)) {

                ((Property)aField).makeOwned(this);
                this.properties.add((Property)aField);
                this.money -= 1000;
            }
        }
    }
    //Interaction happened, no need to do anything further
    else return; 
    }


    @Override
        public String toString () { return "Player name: '"+this.name+"', money: '"+this.money+"', isPlaying? "+this.isPlaying+", CurrentLocation: "+this.onBoardLocation+" , type: "+this.strategy.toString()+" , Properties: "+this.properties.size(); }
}


class Tactical_Player extends Player {

    public Boolean chance;

    public Tactical_Player (String name, Strategy strategy) {
        super (name,strategy);
        this.chance = true; //Chance to buy, starts as true
    }

    
    @Override
    public void doStrategy (Boolean interact_happened, Field aField) {

        //Chance is true to buy
        if (this.chance) {

            this.chance = false;
            //No interaction means either owned/not owned
            if (!interact_happened) {

                //Owned by thisPlayer means they can buy a house on it
                if ( ((Property)aField).isOwned() && (((Property)aField).player.name).equals(this.name) ) {

                    ((Property)aField).increaseStep();

                    if ( !(((Property)aField).hasHouse()) && (this.money > 4000)) {
                        ((Property)aField).makeHouse();
                        this.money -= 4000;
                    }
                }
                //Unowned by this player
                else {
                    if(this.money > 1000) {

                        ((Property)aField).makeOwned(this);
                        this.properties.add((Property)aField);
                        this.money -= 1000;
                    }
                }
            }
        }
        //If chance is false to buy, then next round will be true
        else {

            this.chance = true;
            if ( (aField.getClass() == Property.class) && ((Property)aField).isOwned() &&(((Property)aField).player.name).equals(this.name) ) { //This checks if the class is a property in the first place.
                ((Property)aField).increaseStep();
            }
        }
    }


    @Override
        public String toString () { return "Player name: '"+this.name+"', money: '"+this.money+"', isPlaying? "+this.isPlaying+", CurrentLocation: "+this.onBoardLocation+" , type: "+this.strategy.toString()+", curr_chance: "+this.chance+" , Properties: "+this.properties.size(); }
}