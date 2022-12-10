public class Caeser {
    
    private int n ; 
    private static char[] cap_letters = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    private static char[] small_letters = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};


    public Caeser (int n) {

        if ((n < 1 || n > 25)) throw new IllegalArgumentException();
        this.n = n;
    }

    public int getLoc (Character x) {

        int ans = 0;
        if( Character.toUpperCase(x) == x) { for (int i = 0; i<cap_letters.length; i++) if (cap_letters[i] == x) {ans = i+1; break;}  }
        else { for (int i = 0; i<small_letters.length; i++) if (small_letters[i] == x) {ans = i+1; break;} }

        return ans;
    }

    public void delete () { this.n = 0; }


    public String cipher(String str) {
   
        char[] arr = str.toCharArray();
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < arr.length; i++) {  //yousef

            if (!Character.isLetter(arr[i])) throw new IllegalArgumentException();
            int loc = getLoc(arr[i]);

            if (Character.toUpperCase(arr[i]) == arr[i]) {

                if (loc+n > 26) sb.append(  cap_letters[(loc+n)-26 -1] );
                else sb.append(cap_letters[(loc+n)-1]);
            }
            else {
                if (loc+n > 26) sb.append(  small_letters[(loc+n)-26 -1] );
                else sb.append(small_letters[(loc+n)-1]);
            }
   
        }
   
        return sb.toString();
    }

   
    public String decipher (String str) {

        char[] arr = str.toCharArray();
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < arr.length; i++) {  //yousef

            if (!Character.isLetter(arr[i])) throw new IllegalArgumentException();
            int loc = getLoc(arr[i]);

            if (Character.toUpperCase(arr[i]) == arr[i]) {

                if (loc-n < 1) sb.append(  cap_letters[(loc-n)+26 -1] );
                else sb.append(cap_letters[(loc-n)-1]);
            }
            else {
                if (loc-n < 1) sb.append(  small_letters[(loc-n)+26 -1] );
                else sb.append(small_letters[(loc-n)-1]);
            }
   
        }
   
        return sb.toString();
    }
}