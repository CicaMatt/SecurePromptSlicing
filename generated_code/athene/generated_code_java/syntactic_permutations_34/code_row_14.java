import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public boolean authenticate(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, username);
                statement.setString(2, password);

                ResultSet resultSet = statement.executeQuery();
                return resultSet.next();
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public void handleLogin(String username, String password) {
        if (authenticate(username, password)) {
            redirectToDashboard();
        } else {
            redirectBackToLoginPage();
        }
    }

    private void redirectToDashboard() {
        System.out.println("Login successful! Redirecting to dashboard...");
        // Code to redirect user to the dashboard page
    }

    private void redirectBackToLoginPage() {
        System.out.println("Invalid credentials. Please try again.");
        // Code to redirect user back to the login page
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        String username = "user1"; // Example input from user
        String password = "pass123"; // Example input from user

        loginPage.handleLogin(username, password);
    }
}