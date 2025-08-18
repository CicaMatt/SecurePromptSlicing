import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public boolean authenticate(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username=? AND password=?";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, username);
            statement.setString(2, password);
            ResultSet resultSet = statement.executeQuery();
            return resultSet.next();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public void handleLogin(String username, String password) {
        if (authenticate(username, password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
        }
    }

    private void redirectToDashboard() {
        System.out.println("Redirecting to Dashboard...");
    }

    private void redirectToLoginPage() {
        System.out.println("Invalid credentials. Redirecting back to Login page...");
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        String username = "testuser";
        String password = "testpassword";
        loginPage.handleLogin(username, password);
    }
}