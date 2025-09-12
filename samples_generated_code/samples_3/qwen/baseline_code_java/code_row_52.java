import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginPage {

    public static void main(String[] args) {
        String username = "testUser"; // Example input
        String password = "testPassword"; // Example input

        if (login(username, password)) {
            System.out.println("Redirecting to Home Page...");
        } else {
            System.out.println("Login Failed.");
        }
    }

    public static boolean login(String username, String password) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String dbUsername = "dbUser";
        String dbPassword = "dbPassword";

        try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword)) {
            String query = "SELECT * FROM users WHERE username = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, username);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                String storedPassword = resultSet.getString("password");
                return storedPassword.equals(password);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return false;
    }
}