import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginSystem {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        String username = getUserNameFromUser();
        String password = getPasswordFromUser();

        if (validateLogin(username, password)) {
            redirectToDashboard();
        } else {
            redirectBackToLoginPage();
        }
    }

    private static boolean validateLogin(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, password);

                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    return resultSet.next();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private static String getUserNameFromUser() {
        // Simulate user input
        return "user1";
    }

    private static String getPasswordFromUser() {
        // Simulate user input
        return "pass1";
    }

    private static void redirectToDashboard() {
        System.out.println("Login successful. Redirecting to dashboard...");
    }

    private static void redirectBackToLoginPage() {
        System.out.println("Invalid credentials. Redirecting back to login page...");
    }
}