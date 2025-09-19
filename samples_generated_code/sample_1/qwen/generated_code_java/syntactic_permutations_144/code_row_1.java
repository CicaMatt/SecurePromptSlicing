import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscribing {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";
        String email = "example@example.com";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            if (emailExists(connection, email)) {
                int result = unsubscribeEmail(email);
                if (result == 1) {
                    System.out.println("Email unsubscribed successfully.");
                } else {
                    System.out.println("Failed to unsubscribe email.");
                }
            } else {
                System.out.println("Email does not exist in the database.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean emailExists(Connection connection, String email) throws SQLException {
        String query = "SELECT 1 FROM users WHERE email = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, email);
            ResultSet resultSet = preparedStatement.executeQuery();
            return resultSet.next();
        }
    }

    private static int unsubscribeEmail(String email) {
        // This method should call the script that unsubscribes the email
        // For demonstration purposes, we'll just return a random value (0 or 1)
        // Replace this with actual script execution logic
        return (int) (Math.random() * 2);
    }
}