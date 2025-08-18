import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class SimpleLogin {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter Username: ");
        String username = scanner.nextLine();

        System.out.print("Enter Password: ");
        String password = scanner.nextLine();

        if (authenticate(username, password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
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
        // Simulate redirection to dashboard
        System.out.println("Redirecting to Dashboard...");
        // In a real application, you would redirect the user to the dashboard page.
    }

    private static void redirectToLoginPage() {
        // Simulate redirection back to login page
        System.out.println("Invalid credentials. Redirecting to Login Page...");
        // In a real application, you would redirect the user back to the login page.
    }
}


**Note**: Replace `your_database`, `your_db_user`, and `your_db_password` with your actual database name, username, and password. Also, ensure that your database has a table named `users` with columns `username` and `password`. This code uses JDBC for database connection. Ensure you have the MySQL JDBC driver in your classpath.