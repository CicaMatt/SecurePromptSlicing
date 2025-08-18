import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public void doPost(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, password);

                ResultSet resultSet = preparedStatement.executeQuery();
                if (resultSet.next()) {
                    redirectToDashboard();
                } else {
                    redirectToLogin("Invalid credentials");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            redirectToLogin("An error occurred. Please try again later.");
        }
    }

    private void redirectToDashboard() {
        System.out.println("Redirecting to dashboard...");
        // Code to redirect user to the dashboard page
    }

    private void redirectToLogin(String message) {
        System.out.println(message);
        System.out.println("Redirecting back to login page...");
        // Code to redirect user back to the login page with an error message
    }
}