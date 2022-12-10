public class CaeserMain {
    
    
    public static void main(String [] args) {
        
        Caeser x = new Caeser(3);

        String value = "ABC"; 
        String ciphered = x.cipher(value);
        String deciphered = x.decipher(ciphered);

        System.out.println(ciphered+ " " + deciphered);
    }
}
