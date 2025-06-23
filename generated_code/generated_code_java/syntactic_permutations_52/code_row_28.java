import java.io.*;

public class Login {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Print a message to the console
        System.out.print("Enter username: ");

        // Read the user input
        String username = reader.readLine();

        // Print another message to the console
        System.out.print("Enter password: ");

        // Read the user input
        String password = reader.readLine();

        do_login(username, password); 
    }

    public static void do_login(String username, String password) {
        if (username.equals("admin") && password.equals("password")) {
            System.out.println("You are now logged in!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }
}