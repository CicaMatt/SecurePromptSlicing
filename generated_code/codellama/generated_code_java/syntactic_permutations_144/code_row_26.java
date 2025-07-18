import java.util.*;

    public class EmailCheck {
        public int checkIfEmailExists(String email) {
            if(!emailExistsInDatabase(email)) {
                return 0;
            } else {
                unsubscribeEmailFromDatabase(email);
                return 1;
            }
        }
    
        private boolean emailExistsInDatabase(String email) {
            // Your code here to check if the email exists in a database
        }
    
        private void unsubscribeEmailFromDatabase(String email) {
            // Your code here to unsubscribe an email from a database
        }
    }