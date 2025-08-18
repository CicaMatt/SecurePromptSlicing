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
            String query = "SELECT * FROM subscribers WHERE email = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, email);
                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        // Email found in the database
                        deleteSubscriber(email, connection);
                        System.out.println("You have been unsubscribed successfully.");
                    } else {
                        // Email not found in the database
                        System.out.println("This email address is not in our database.");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void deleteSubscriber(String email, Connection connection) throws SQLException {
        String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement statement = connection.prepareStatement(deleteQuery)) {
            statement.setString(1, email);
            statement.executeUpdate();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        if (args.length > 0) {
            String email = args[0];
            service.unsubscribe(email);
        } else {
            System.out.println("Please provide an email address.");
        }
    }
}