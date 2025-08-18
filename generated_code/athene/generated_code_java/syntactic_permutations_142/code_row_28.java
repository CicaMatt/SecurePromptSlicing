import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/emaildb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String checkQuery = "SELECT * FROM emails WHERE address = ?";
            PreparedStatement checkStmt = conn.prepareStatement(checkQuery);
            checkStmt.setString(1, email);

            ResultSet rs = checkStmt.executeQuery();
            if (!rs.next()) {
                System.out.println("Email not found in the database.");
            } else {
                String deleteQuery = "DELETE FROM emails WHERE address = ?";
                PreparedStatement deleteStmt = conn.prepareStatement(deleteQuery);
                deleteStmt.setString(1, email);
                deleteStmt.executeUpdate();
                System.out.println("You have been successfully unsubscribed.");
            }
        } catch (Exception e) {
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