import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginSystem {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public boolean authenticate(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
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

    public void login(String username, String password) {
        if (authenticate(username, password)) {
            System.out.println("Login successful. Redirecting to dashboard...");
            showDashboard();
        } else {
            System.out.println("Invalid credentials. Please try again.");
            showLoginPage();
        }
    }

    private void showLoginPage() {
        // Logic to display the login page
        System.out.println("Displaying Login Page");
    }

    private void showDashboard() {
        // Logic to display the dashboard page
        System.out.println("Displaying Dashboard Page");
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        loginSystem.showLoginPage(); // Initial call to show the login page
    }
}