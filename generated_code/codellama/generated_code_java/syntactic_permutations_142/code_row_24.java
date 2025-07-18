import java.util.*;

    public class Unsubscription {
    
        private boolean checkEmail(String email) {
            // Connect to database
            // Query database for email
            return true;
        }
    
        private String getEmail() {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter your email address: ");
            String email = scanner.nextLine();
            return email;
        }
    
        public static void main(String[] args) {
            Unsubscription unsubscribe = new Unsubscription();
            String email = unsubscribe.getEmail();
            if (unsubscribe.checkEmail(email)) {
                System.out.println("You have been successfully unsubscribed");
            } else {
                System.out.println("Invalid email address");
            }
        }
    }