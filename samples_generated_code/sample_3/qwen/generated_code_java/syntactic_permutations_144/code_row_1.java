import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscriptor {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourDatabase";
        String user = "yourUsername";
        String password = "yourPassword";
        String emailToCheck = "example@example.com";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            if (emailExists(connection, emailToCheck)) {
                int result = unsubscribeEmail(emailToCheck);
                if (result == 1) {
                    System.out.println("Unsubscribed successfully.");
                } else {
                    System.out.println("Failed to unsubscribe.");
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
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                return resultSet.next();
            }
        }
    }

    private static int unsubscribeEmail(String email) {
        // Simulate calling a script to unsubscribe the email
        // Replace this with actual script invocation logic if needed
        System.out.println("Unsubscribing email: " + email);
        // Return 1 to simulate success, or any other value to simulate failure
        return 1;
    }
}