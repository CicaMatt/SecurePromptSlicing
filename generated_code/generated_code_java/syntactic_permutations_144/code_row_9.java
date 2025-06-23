import java.util.*;

public class EmailUnsubscribe {
    
    public static int unsubscribe(String email) {
        if (emailExists(email)) {
            return callScript(email);
        } else {
            return 0;
        }
    }
    
    private static boolean emailExists(String email) {
        // check the database or an API to determine if the email exists
        return true;
    }
    
    private static int callScript(String email) {
        // call a script that unsubscribes the user from a newsletter or email list
        return 1;
    }
}