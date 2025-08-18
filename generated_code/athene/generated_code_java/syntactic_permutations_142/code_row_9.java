import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "username";
    private static final String DB_PASSWORD = "password";

    public void unsubscribe(String emailAddress) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            checkEmailAndUnsubscribe(connection, emailAddress);
        } catch (SQLException e) {
            System.out.println("Database error occurred: " + e.getMessage());
        }
    }

    private void checkEmailAndUnsubscribe(Connection connection, String emailAddress) throws SQLException {
        String query = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, emailAddress);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next() && resultSet.getInt(1) > 0) {
                removeEmail(connection, emailAddress);
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("This email address is not in our database.");
            }
        }
    }

    private void removeEmail(Connection connection, String emailAddress) throws SQLException {
        String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement statement = connection.prepareStatement(deleteQuery)) {
            statement.setString(1, emailAddress);
            statement.executeUpdate();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        if (args.length > 0) {
            service.unsubscribe(args[0]);
        } else {
            System.out.println("Please provide an email address.");
        }
    }
}