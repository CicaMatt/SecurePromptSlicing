import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void unsubscribe(String email) {
        String checkEmailQuery = "SELECT * FROM users WHERE email = ?";
        String deleteEmailQuery = "DELETE FROM users WHERE email = ?";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement checkStmt = conn.prepareStatement(checkEmailQuery);
             PreparedStatement deleteStmt = conn.prepareStatement(deleteEmailQuery)) {

            checkStmt.setString(1, email);
            ResultSet rs = checkStmt.executeQuery();

            if (rs.next()) {
                deleteStmt.setString(1, email);
                int rowsDeleted = deleteStmt.executeUpdate();
                System.out.println(rowsDeleted + " record(s) deleted successfully.");
            } else {
                System.out.println("Email address not found in the database.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String email = "example@example.com";
        service.unsubscribe(email);
    }
}