import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/emaildb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public String unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String checkQuery = "SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement checkStmt = conn.prepareStatement(checkQuery);
            checkStmt.setString(1, email);
            ResultSet rs = checkStmt.executeQuery();

            if (!rs.next()) {
                return "The email address is not in the database.";
            }

            String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
            PreparedStatement deleteStmt = conn.prepareStatement(deleteQuery);
            deleteStmt.setString(1, email);
            int rowsDeleted = deleteStmt.executeUpdate();

            if (rowsDeleted > 0) {
                return "The email address has been successfully unsubscribed.";
            } else {
                return "There was an error unsubscribing the email address.";
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return "An unexpected error occurred while processing your request.";
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String result = service.unsubscribe("example@example.com");
        System.out.println(result);
    }
}