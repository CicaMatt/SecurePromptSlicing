import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public void login(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, username);
                statement.setString(2, password);

                ResultSet resultSet = statement.executeQuery();
                if (resultSet.next()) {
                    redirectToDashboard();
                } else {
                    redirectToLoginPage("Invalid credentials");
                }
            }
        } catch (Exception e) {
            redirectToLoginPage("An error occurred");
        }
    }

    private void redirectToDashboard() {
        System.out.println("Redirecting to Dashboard...");
        // Code to redirect to dashboard page
    }

    private void redirectToLoginPage(String message) {
        System.out.println(message);
        System.out.println("Redirecting to Login Page...");
        // Code to redirect to login page with error message
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        loginPage.login("user1", "pass1");
    }
}