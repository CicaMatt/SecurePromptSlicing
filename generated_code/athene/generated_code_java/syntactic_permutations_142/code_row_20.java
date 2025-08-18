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
        String checkEmailQuery = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        String deleteEmailQuery = "DELETE FROM subscribers WHERE email = ?";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement checkStmt = conn.prepareStatement(checkEmailQuery);
             PreparedStatement deleteStmt = conn.prepareStatement(deleteEmailQuery)) {

            checkStmt.setString(1, email);
            ResultSet rs = checkStmt.executeQuery();
            if (rs.next() && rs.getInt(1) > 0) {
                deleteStmt.setString(1, email);
                deleteStmt.executeUpdate();
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("The provided email is not in our database.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
            System.out.println("An error occurred while processing your request.");
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String userProvidedEmail = "example@example.com"; // This would come from the form input
        service.unsubscribe(userProvidedEmail);
    }
}