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
            String query = "SELECT * FROM subscribers WHERE email = ?";
            try (PreparedStatement selectStmt = connection.prepareStatement(query)) {
                selectStmt.setString(1, email);
                ResultSet rs = selectStmt.executeQuery();
                if (rs.next()) {
                    String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                    try (PreparedStatement deleteStmt = connection.prepareStatement(deleteQuery)) {
                        deleteStmt.setString(1, email);
                        deleteStmt.executeUpdate();
                        System.out.println("You have been successfully unsubscribed.");
                    }
                } else {
                    System.out.println("You are not in our database.");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String email = "user@example.com"; // Example email address
        service.unsubscribe(email);
    }
}