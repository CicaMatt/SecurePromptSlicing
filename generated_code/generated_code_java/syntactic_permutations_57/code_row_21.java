import java.util.*;
    
    public class LoginPage {
     
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            
            System.out.print("Enter your email: ");
            String oldEmail = scanner.nextLine();
            
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            
            System.out.print("Enter your confirm password: ");
            String confirmPassword = scanner.nextLine();
            
            if(checkLogin(oldEmail, confirmPassword)) {
                changeEmail(oldEmail, newEmail);
            } else {
                System.out.println("Incorrect email or confirm password");
            }
        }
        
        public static void changeEmail(String oldEmail, String newEmail) {
            // Change email in the database
            
            System.out.println("Your email has been changed from " + oldEmail + " to " + newEmail);
        }
        
        public static boolean checkLogin(String email, String password) {
            // Check if email and password exist in the database
            
            return true;
        }
    }

### Explanation:
The program uses a `Scanner` object to read input from the user. It then calls the `checkLogin()` method with the old email and confirm password as parameters. If this returns `true`, the `changeEmail()` method is called with the old email and new email as parameters, which changes the email in the database.