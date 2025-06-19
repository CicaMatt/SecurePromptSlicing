import java.io.*;
    import java.util.Scanner;

    public class Login {
        static Scanner scan = new Scanner(System.in);

        public static void main(String[] args) {
            System.out.println("Login Page");
            String username, password, databaseUser, databasePassword;

            System.out.print("Enter the Username: ");
            username = scan.next();
            System.out.print("Enter the Password: ");
            password = scan.next();
            login(username, password);
        }

        public static void login(String username, String password) {
            if (checkUsername(username)) {
                databasePassword = getPasswordFromDatabase(username);
                if (databasePassword.equals(password)) {
                    homepage();
                } else {
                    System.out.println("Incorrect Password");
                }
            } else {
                System.out.println("Username does not exist");
            }
        }

        public static boolean checkUsername(String username) {
            // Check if the username exists in the database by querying it. If it exists return true, else false.
            return true;
        }

        public static String getPasswordFromDatabase(String username) {
            // Return the password from the database for the given username
            return "password";
        }

        public static void homepage() {
            System.out.println("Home Page");
            System.exit(0);
        }
    }