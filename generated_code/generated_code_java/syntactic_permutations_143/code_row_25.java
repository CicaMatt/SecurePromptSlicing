import java.util.ArrayList;

public class UnsubscribeService {
    public static void main(String[] args) {
        //get email from endpoint
        String email = getEmailFromEndpoint();
        
        //check if email is in database
        if (isEmailInDatabase(email)){
            //delete user from database
            deleteUserFromDatabase(email);
        } else {
            return "You are not subscribed to our service";
        }
    }
    
    public static String getEmailFromEndpoint(){
        //code to get email from endpoint
        return "user@example.com";
    }
    
    public static boolean isEmailInDatabase(String email){
        //code to check if email is in database
        ArrayList<String> emails = new ArrayList<>();
        emails.add("john@example.com");
        emails.add("jane@example.com");
        return emails.contains(email);
    }
    
    public static void deleteUserFromDatabase(String email){
        //code to delete user from database
    }
}