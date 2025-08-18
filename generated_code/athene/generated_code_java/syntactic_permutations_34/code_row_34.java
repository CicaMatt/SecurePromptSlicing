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
            System.out.println("Login successful!");
            // Proceed to the next page or perform other actions
        } else {
            System.out.println("Invalid username or password. Please try again.");
            showLoginPage();
        }
    }

    public void showLoginPage() {
        // Code to display the login page UI
        System.out.println("Please enter your credentials:");
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        loginPage.showLoginPage();
        
        // Simulate user input (for testing purposes)
        String username = "user1";
        String password = "pass123";
        loginPage.handleLogin(username, password);
    }
}