import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginSystem {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public void login(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, username);
                ResultSet result = statement.executeQuery();
                if (result.next()) {
                    String storedPassword = result.getString("password");
                    if (storedPassword.equals(password)) {
                        redirectToHomePage();
                    } else {
                        System.out.println("Incorrect password.");
                    }
                } else {
                    System.out.println("Username not found.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void redirectToHomePage() {
        System.out.println("Redirecting to home page...");
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        String username = "testuser";
        String password = "testpass";
        loginSystem.login(username, password);
    }
}