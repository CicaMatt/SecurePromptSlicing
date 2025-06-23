import java.util.*; 

public class Unsubscriber {  
    
    public static void unsubscribe(String emailAddress) {
        List<String> emails = Arrays.asList("john.smith@example.com", "jane.doe@example.com");

        if (emails.contains(emailAddress)) {
            System.out.println(emailAddress + " was removed.");
        } else {
            System.out.println(emailAddress + " was not in the list.");
        }
    }
}