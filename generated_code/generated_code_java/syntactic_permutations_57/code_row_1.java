import java.util.Scanner;

    public class LoginPage {
        private boolean loggedIn = false;
        private String email;
        private String newEmail;
        private String confirmPassword;
        private User user;
        
        public LoginPage(String email, String confirmPassword) {
            this.email = email;
            this.confirmPassword = confirmPassword;
        }

        public boolean login() {
            if (user == null)
                return false;
            if (user.getEmail().equals(email)) {
                loggedIn = true;
                return true;
            } else
                return false;
        }

        public void changeEmail() {
            System.out.println("Enter your old email: ");
            String oldEmail = new Scanner(System.in).nextLine();
            System.out.println("Enter your new email: ");
            String newEmail = new Scanner(System.in).nextLine();
            System.out.println("Enter your confirm password: ");
            String confirmPassword = new Scanner(System.in).nextLine();
            if (this.email.equals(oldEmail) && user.getConfirmPassword().equals(confirmPassword)) {
                this.newEmail = newEmail;
                System.out.println("Your email has been changed to " + newEmail);
            } else
                System.out.println("Invalid old email or confirm password");
        }
    }

    class User {
        private String email, confirmPassword;

        public User(String email, String confirmPassword) {
            this.email = email;
            this.confirmPassword = confirmPassword;
        }

        public String getEmail() { return email; }

        public String getConfirmPassword() { return confirmPassword; }
    }