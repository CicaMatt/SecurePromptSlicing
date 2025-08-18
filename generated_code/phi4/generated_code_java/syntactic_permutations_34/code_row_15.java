import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginApplication {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/login_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter Username:");
        String username = scanner.nextLine();
        
        System.out.println("Enter Password:");
        String password = scanner.nextLine();

        if (authenticate(username, password)) {
            redirectToDashboard();
        } else {
            System.out.println("Invalid credentials. Redirecting to login page...");
        }
    }

    private static boolean authenticate(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?")) {

            stmt.setString(1, username);
            stmt.setString(2, password);

            ResultSet rs = stmt.executeQuery();

            return rs.next();
        
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private static void redirectToDashboard() {
        try {
            // Simulate redirection to dashboard
            System.out.println("Redirecting to Dashboard...");
            Thread.sleep(1000);
            System.out.println("Welcome to the Dashboard!");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}


Make sure you have a MySQL database set up with a `login_db` schema and a table named `users` having columns `username` and `password`. You can adjust the `DB_URL`, `USER`, and `PASS` constants to match your database configuration.