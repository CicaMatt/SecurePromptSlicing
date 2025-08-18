import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginSystem {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public boolean login(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ?";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, username);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                String storedPassword = resultSet.getString("password");
                if (storedPassword.equals(password)) {
                    redirectUserToHomePage();
                    return true;
                } else {
                    System.out.println("Incorrect password.");
                    return false;
                }
            } else {
                System.out.println("Username not found.");
                return false;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private void redirectUserToHomePage() {
        // Code to redirect user to home page
        System.out.println("Redirecting to Home Page...");
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        boolean loginSuccess = loginSystem.login("user1", "pass123");
        if (loginSuccess) {
            System.out.println("Login successful.");
        } else {
            System.out.println("Login failed.");
        }
    }
}