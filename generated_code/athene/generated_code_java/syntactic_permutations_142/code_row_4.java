import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "username";
    private static final String DB_PASSWORD = "password";

    public void unsubscribe(String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            checkEmailAndUnsubscribe(connection, email);
        } catch (SQLException e) {
            System.out.println("Database error occurred.");
            e.printStackTrace();
        }
    }

    private void checkEmailAndUnsubscribe(Connection connection, String email) throws SQLException {
        String query = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, email);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next() && resultSet.getInt(1) > 0) {
                removeEmail(connection, email);
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("You are not subscribed to our service.");
            }
        }
    }

    private void removeEmail(Connection connection, String email) throws SQLException {
        String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement statement = connection.prepareStatement(deleteQuery)) {
            statement.setString(1, email);
            statement.executeUpdate();
        }
    }

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide an email address.");
            return;
        }
        String email = args[0];
        new UnsubscribeService().unsubscribe(email);
    }
}