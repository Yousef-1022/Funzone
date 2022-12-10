import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.ConcurrentHashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.atomic.AtomicInteger;

import java.util.Collections;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.ThreadLocalRandom;


public class FieldRace {


    final static int PLAYER_COUNT = 10;
    final static int CHECKPOINT_COUNT = 20;


    static AtomicBoolean isOn; 
    static ConcurrentHashMap <String,Integer> scores;
    static List<AtomicInteger> checkpointScores;  //    Player_Count amount
    static List<BlockingQueue<AtomicInteger>> cQ; 
    static List<BlockingQueue<AtomicInteger>> checkpointQueues; //  Checkpoint_Count amount


    //  Initializing main values
    FieldRace () {
        
        isOn = new AtomicBoolean(true);
        scores = new ConcurrentHashMap<>();
        checkpointScores = new ArrayList<>();
        cQ = new ArrayList<>();

        for (int i=0; i<PLAYER_COUNT; i++) {
            checkpointScores.add(new AtomicInteger(0));
            scores.put(String.valueOf(i), 0);
        }

        for (int i=0; i<CHECKPOINT_COUNT; i++) {
            BlockingQueue<AtomicInteger> bq = new ArrayBlockingQueue<AtomicInteger>(CHECKPOINT_COUNT);
            cQ.add(bq);
        }
        checkpointQueues = Collections.synchronizedList(cQ);
    }  

    List<String> printScores () {

        List<String>Results = new ArrayList<String>();
        List<String>IDs = new ArrayList<String>(scores.keySet());
        for (String ID : IDs) {
            String output = (ID+"="+scores.get(ID)+" ");
            Results.add(output);
        }
        return Results;
    }


    //  Checkpoint activity
    void repeatedActivity_CHECKPOINT (final int checkpointNum) {
        
        BlockingQueue<AtomicInteger> theCheckpoint = checkpointQueues.get(checkpointNum);
        AtomicInteger element = null;
        while (isOn.get()) {
            
            try {
                element = theCheckpoint.poll(2,TimeUnit.SECONDS);
            } catch (InterruptedException e) { System.out.println("repeatedActivity_CHECKPOINT: "+checkpointNum+" interrupted at poll"); }
                
            if(element != null) {
                
                final int theRandomValue = ThreadLocalRandom.current().nextInt(10, 100);
                element.set(theRandomValue);
                
                synchronized (element) {
                    element.notify();
                }
            }      
        }          
    }

    void repeatedActivity_PLAYER (final int playerNum) {
        
        
        while (isOn.get()) {
        
            int checkPointIDX = ThreadLocalRandom.current().nextInt(0, CHECKPOINT_COUNT);
            BlockingQueue<AtomicInteger> randomCheckpoint = checkpointQueues.get(checkPointIDX);

            //  time to take player to go to checkpoint
            try {
                long waitTime = ThreadLocalRandom.current().nextInt(500, 2000);
                Thread.sleep(waitTime);
            } catch (InterruptedException e) { System.out.println("repeatedActivity_PLAYER: "+playerNum+" interrupted at 0.5-2 seconds sleep"); }


            randomCheckpoint.add(checkpointScores.get(playerNum));

            //Waiting for notification
            boolean check = true;
            while(check && isOn.get()) {
                
                try {
                    synchronized(checkpointScores.get(playerNum)) {
                        checkpointScores.get(playerNum).wait(3000);
                    }
                } catch (InterruptedException e) { System.out.println("repeatedActivity_PLAYER: "+playerNum+" interrupted at 3 seconds wait"); }
                    
                if(checkpointScores.get(playerNum).get() != 0) {
                    check = false;
                }
            }

            if (checkpointScores.get(playerNum).get() != 0) {

                int oldScore = scores.get(String.valueOf(playerNum));
                scores.put(String.valueOf(playerNum), (oldScore+checkpointScores.get(playerNum).get()));
                System.out.println("Player "+playerNum+" got "+checkpointScores.get(playerNum).get()+" at checkpoint "+checkPointIDX);
                checkpointScores.get(playerNum).set(0);
            }
        }
    }
    

    void setToFalse () {
        isOn.set(false);
    }
    
    //  11th thread printer
    void plusOneThread () {

        while (isOn.get()) {
            try {
                Thread.sleep(1000);
                System.out.println(printScores());
            }
            catch (InterruptedException e) { System.out.println("plusOneThread got interrupted during sleep"); }
        }
    }


    public static void main (String args[]) {


        FieldRace fr = new FieldRace();
        ExecutorService ex = Executors.newFixedThreadPool(PLAYER_COUNT + CHECKPOINT_COUNT + 1);


        for (int i=0; i<PLAYER_COUNT; i++) {
            
            final int finali = i;
            ex.submit( () -> { fr.repeatedActivity_PLAYER(finali); });
        }

        for (int i=0; i<CHECKPOINT_COUNT; i++) {
            
            final int finali = i;
            ex.submit( () -> { fr.repeatedActivity_CHECKPOINT(finali); });
        }

        //  Last thread to count
        ex.submit( () -> { fr.plusOneThread();} );



        //  After 10 seconds, main shutsdown the executor
        try {
            Thread.sleep(20000);
        } catch (InterruptedException E) { System.out.println("Main after 10 seconds got interrupted"); }
        
        fr.setToFalse();
        ex.shutdown();

        try {
            ex.awaitTermination(3, TimeUnit.SECONDS);
        } catch (InterruptedException E) {}
        ex.shutdownNow();
        

        //  Now print the total score one last time
        System.out.println(fr.printScores()+" -> "+scores.entrySet().stream().mapToInt(E -> E.getValue()).sum());
    }
}