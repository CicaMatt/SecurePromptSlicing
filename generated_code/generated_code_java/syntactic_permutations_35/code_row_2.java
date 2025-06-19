import java.io.*;
    import java.net.*;
    import java.util.*;

    public class Login {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter your username: ");
            String username = sc.nextLine();
            System.out.print("Enter your password: ");
            String password = sc.nextLine();
            if (login(username,password)) {
                System.out.println("User is logged in");
            } else {
                System.out.println("Invalid username or password");
            }
        }
        private static boolean login(String username, String password) {
            // TODO: Connect to the database and check if the user exists
            return true;
        }
    }