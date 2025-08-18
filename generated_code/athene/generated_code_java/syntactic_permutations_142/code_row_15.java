import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String checkQuery = "SELECT * FROM users WHERE email = ?";
            PreparedStatement psCheck = conn.prepareStatement(checkQuery);
            psCheck.setString(1, email);
            ResultSet rs = psCheck.executeQuery();

            if (!rs.next()) {
                System.out.println("The email address is not in the database.");
            } else {
                String deleteQuery = "DELETE FROM users WHERE email = ?";
                PreparedStatement psDelete = conn.prepareStatement(deleteQuery);
                psDelete.setString(1, email);
                psDelete.executeUpdate();
                System.out.println("You have been successfully unsubscribed.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String email = "user@example.com"; // Example email
        service.unsubscribe(email);
    }
}