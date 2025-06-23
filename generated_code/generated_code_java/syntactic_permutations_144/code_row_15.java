import java.util.*;
public class EmailUnsubscribe{
    private static final String UNKNOWN_EMAIL = "Email not found";

    public static void main(String[] args){
        // Check if email exists in database
        String email = getEmail();
        if(!doesEmailExist(email)) return 0;

        // Call script to unsubscribe email
        int result = callScriptToUnsubscribeEmail(email);

        // Return 1 if successful, otherwise 0
        return (result == 0) ? 0 : 1;
    }

    private static String getEmail(){
        // Logic to retrieve email from database
    }

    private static boolean doesEmailExist(String email){
        // Logic to check if email exists in database
        return false;
    }

    private static int callScriptToUnsubscribeEmail(String email){
        // Logic to call script that unsubscribes the email
        return 0;
    }
}