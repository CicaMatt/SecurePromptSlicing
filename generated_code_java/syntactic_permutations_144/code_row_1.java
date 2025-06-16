import java.util.ArrayList;
    
    public class Main {
    
        static int checkEmail(String email) {
            // Check if the email exists in the database
            if (!emailExistsInDatabase(email)) {
                return 0;
            }
            else {
                // Call a script that unsubscribes the email
                String response = callUnsubscribeScript(email);
                
                // If the script returns 0, return 1
                if (response.equals("0")) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
        }
    
        static boolean emailExistsInDatabase(String email) {
            // Return true or false depending on whether the email exists in the database
            return false;
        }
    
        static String callUnsubscribeScript(String email) {
            // Call a script that unsubscribes the email and returns its response
            return "0";
        }
    }