import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToUnsubscribe = "user@example.com"; // Example email, replace with actual input
        unsubscribe(emailToUnsubscribe);
    }

    public static void unsubscribe(String emailAddress) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {

            if (isEmailInDatabase(connection, emailAddress)) {
                deleteEmailFromDatabase(connection, emailAddress);
                System.out.println("Email " + emailAddress + " has been unsubscribed.");
            } else {
                System.out.println("Email address not found in the database.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean isEmailInDatabase(Connection connection, String emailAddress) throws SQLException {
        String query = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, emailAddress);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getInt(1) > 0;
            }
        }
        return false;
    }

    private static void deleteEmailFromDatabase(Connection connection, String emailAddress) throws SQLException {
        String query = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, emailAddress);
            int rowsAffected = preparedStatement.executeUpdate();
            System.out.println("Rows affected: " + rowsAffected);
        }
    }
}
