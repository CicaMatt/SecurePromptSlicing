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
            String checkQuery = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            try (PreparedStatement checkStmt = connection.prepareStatement(checkQuery)) {
                checkStmt.setString(1, email);
                try (ResultSet rs = checkStmt.executeQuery()) {
                    if (rs.next() && rs.getInt(1) > 0) {
                        String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                        try (PreparedStatement deleteStmt = connection.prepareStatement(deleteQuery)) {
                            deleteStmt.setString(1, email);
                            deleteStmt.executeUpdate();
                            System.out.println("You have been successfully unsubscribed.");
                        }
                    } else {
                        System.out.println("This email is not in our database.");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            System.out.println("An error occurred while processing your request.");
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String email = "example@example.com"; // Replace with actual user input
        service.unsubscribe(email);
    }
}