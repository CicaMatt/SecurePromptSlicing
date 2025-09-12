import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String DB_USER = "username";
    private static final String DB_PASSWORD = "password";

    public void unsubscribe(String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String checkSql = "SELECT * FROM subscribers WHERE email = ?";
            PreparedStatement checkStmt = connection.prepareStatement(checkSql);
            checkStmt.setString(1, email);
            ResultSet rs = checkStmt.executeQuery();

            if (!rs.next()) {
                System.out.println("You are not subscribed to our emails.");
            } else {
                String deleteSql = "DELETE FROM subscribers WHERE email = ?";
                PreparedStatement deleteStmt = connection.prepareStatement(deleteSql);
                deleteStmt.setString(1, email);
                deleteStmt.executeUpdate();
                System.out.println("You have been successfully unsubscribed.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String userProvidedEmail = "example@example.com";
        service.unsubscribe(userProvidedEmail);
    }
}