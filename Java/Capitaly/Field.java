abstract class Field {
    
    protected int cost;
    protected int onBoardLocation;

    public abstract int getCost ();
    public abstract String toString ();
    public int getOnBoardLocation () { return this.onBoardLocation; }
}


class Property extends Field {

    private Boolean house;
    private Boolean owned;
    public Player player;
    private int SteppedOn;
    public String name;

    public Property (String name, int onBoardLocation) { 

        this.cost = 1000;
        this.house = false;
        this.owned = false;
        this.SteppedOn = 0;
        this.name = name;
        this.onBoardLocation = onBoardLocation;
    }


    /**
     * Restarts property values back to false,0, and null.
     */
    public void ResetProperty () {
        
        this.owned = false;
        this.player = null;
        this.SteppedOn = 0;
        this.house = false;
    }

    public Boolean hasHouse () { return this.house; }

    public Boolean isOwned () { return this.owned; }


    /**
     * Increases the steps of the Player owner on this property
     */
    public void increaseStep () { this.SteppedOn++; }


    /**
     * Automatically makes the given Player the owner, and increases the amount of steps this owner had on the property 
     * @param thePlayer which is going to own this property
     */
    public void makeOwned (Player thePlayer) { 

        this.owned = true; 
        this.player = thePlayer;
        this.SteppedOn++;
    }
    

    /**
     * Creates a house on this property
     */
    public void makeHouse () { if (this.SteppedOn >= 2) this.house = true; }

    @Override
        public int getCost() { return this.cost; }

    @Override
        public String toString () {
            if (this.player != null) {
                return "Property name: '"+this.name+"', BoardLocation: '"+this.onBoardLocation+"'"+" , Info: [Has House: "+this.house+", isOwned: "+this.owned+", SteppedOnByOwner: "+this.SteppedOn+", Player-Owner: |"+this.player.name+"|]";
            }
            else {
                return "Property name: '"+this.name+"', BoardLocation: '"+this.onBoardLocation+"'"+" , Info: [Has House: "+this.house+", isOwned: "+this.owned+", SteppedOnByOwner: "+this.SteppedOn+", Player-Owner:|NONE|";
            }    
        }
}


class Service extends Field {

    public Service (int someValue, int onBoardLocation) { 

        this.cost = someValue; 
        this.onBoardLocation = onBoardLocation; 
    }

    @Override
        public int getCost() { return this.cost; }

    @Override
        public String toString () { return "Type name: 'Service', cost: '"+this.cost+"', BoardLocation: '"+this.onBoardLocation+"'"; }
}


class Lucky extends Field {

    public Lucky (int someValue, int onBoardLocation) { 

        this.cost = someValue; 
        this.onBoardLocation = onBoardLocation;
    }

    @Override
        public int getCost() { return this.cost; }
    @Override
        public String toString () { return "Type name: 'Lucky', cost: '"+this.cost+"', BoardLocation: '"+this.onBoardLocation+"'"; }

}