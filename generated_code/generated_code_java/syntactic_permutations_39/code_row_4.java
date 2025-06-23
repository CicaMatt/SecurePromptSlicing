import java.util.*;

    public class LoginPage {
        private String username;
        private String password;

        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter Username: ");
            username = scanner.nextLine();
            System.out.println("Enter Password: ");
            password = scanner.nextLine();
            
            if (username.equals("admin") && password.equals("password")) {
                SessionPage sessionPage = new SessionPage(username);
            } else {
                System.out.println("Username or Password is incorrect");
            }
        }
    }

    public class SessionPage {
        private String username;

        public SessionPage(String username) {
            this.username = username;
            System.out.println("Welcome " + username);
            System.out.println("You have successfully logged in.");
        }
    }