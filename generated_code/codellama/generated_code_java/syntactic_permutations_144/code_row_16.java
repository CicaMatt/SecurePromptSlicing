import java.lang.Math;
    
    public class EmailCheck {
        private boolean exists(String email) {
            // Implement checking if the email already exists in the database.
            return false;
        }
        
        private int unsubscribeEmail(String email) {
            // Implement the script that unsubscribes the email.
            return 0;
        }
    
        public int checkEmail(String email) {
            if (!exists(email)) {
                return 0;
            } else {
                if (unsubscribeEmail(email) == 0) {
                    return 1;
                } else {
                    return 0;
                }
            }
        }
    
        public static void main(String[] args) {
            System.out.println(new EmailCheck().checkEmail("test@example.com"));
        }
    }