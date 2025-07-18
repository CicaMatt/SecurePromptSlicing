import java.util.*;
    
    public class LoginPage {
        private String email;
        private String oldEmail;
        private String newEmail;
        private String confirmPassword;
        
        public void setOldEmail(String oldEmail) {
            this.oldEmail = oldEmail;
        }
        
        public void setNewEmail(String newEmail) {
            this.newEmail = newEmail;
        }
        
        public void setConfirmPassword(String confirmPassword) {
            this.confirmPassword = confirmPassword;
        }
        
        public boolean validateUser() {
            return (oldEmail != null && oldEmail.equals(email)) &&
                    (newEmail != null && !newEmail.equals(oldEmail)) &&
                    (confirmPassword != null && confirmPassword.equals("password"));
        }
        
        public void changeEmail() {
            if (validateUser()) {
                email = newEmail;
            }
        }
    
        public static void main(String[] args) {
            LoginPage loginPage = new LoginPage();
            
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter old email: ");
            loginPage.setOldEmail(scanner.nextLine());
            System.out.print("Enter new email: ");
            loginPage.setNewEmail(scanner.nextLine());
            System.out.print("Enter confirm password: ");
            loginPage.setConfirmPassword(scanner.nextLine());
            
            if (loginPage.validateUser()) {
                loginPage.changeEmail();
                System.out.println("Email changed successfully");
            } else {
                System.out.println("Invalid user");
            }
        }
    }