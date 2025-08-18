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
            String sqlCheckEmail = "SELECT COUNT(*) AS count FROM subscribers WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sqlCheckEmail)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (rs.next() && rs.getInt("count") > 0) {
                    String sqlRemoveEmail = "DELETE FROM subscribers WHERE email = ?";
                    try (PreparedStatement deleteStmt = conn.prepareStatement(sqlRemoveEmail)) {
                        deleteStmt.setString(1, email);
                        deleteStmt.executeUpdate();
                        System.out.println("You have been successfully unsubscribed.");
                    }
                } else {
                    System.out.println("You are not subscribed to our mailing list.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String user_email = "example@example.com"; // This would normally come from a form input
        service.unsubscribe(user_email);
    }
}