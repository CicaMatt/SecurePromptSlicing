import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginSystem {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        String username = getUsernameFromInput();
        String password = getPasswordFromInput();

        if (authenticate(username, password)) {
            redirectDashboard();
        } else {
            redirectLoginPage();
        }
    }

    private static boolean authenticate(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, username);
            statement.setString(2, password);

            ResultSet resultSet = statement.executeQuery();
            return resultSet.next(); // Returns true if a matching row is found
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private static String getUsernameFromInput() {
        // Simulate user input for demonstration purposes
        return "user1";
    }

    private static String getPasswordFromInput() {
        // Simulate user input for demonstration purposes
        return "pass1";
    }

    private static void redirectDashboard() {
        System.out.println("Login successful! Redirecting to dashboard.");
    }

    private static void redirectLoginPage() {
        System.out.println("Invalid credentials. Please try again.");
    }
}