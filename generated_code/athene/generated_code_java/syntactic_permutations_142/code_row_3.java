import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "youruser";
    private static final String DB_PASSWORD = "yourpassword";

    public void unsubscribe(String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            checkEmailAndRemove(connection, email);
        } catch (SQLException e) {
            System.out.println("Database connection problem");
            e.printStackTrace();
        }
    }

    private void checkEmailAndRemove(Connection connection, String email) throws SQLException {
        String query = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (rs.next() && rs.getInt(1) > 0) {
                removeEmail(connection, email);
            } else {
                System.out.println("You are not in our database.");
            }
        }
    }

    private void removeEmail(Connection connection, String email) throws SQLException {
        String query = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
            System.out.println("You have been successfully unsubscribed.");
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String email = "example@example.com"; // This should be the user input
        service.unsubscribe(email);
    }
}