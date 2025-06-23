import java.util.*;

public class Info {
    
    public String info(String user) {
        // Create a new random object
        Random rand = new Random();
        
        // Generate a random number from 1 to 500 and cast it to int
        int num = (int)(rand.nextDouble() * 500);
        
        // Return the username email and ssn
        return user + ": " + user + "@email.com" + ": " + num;
    }
}