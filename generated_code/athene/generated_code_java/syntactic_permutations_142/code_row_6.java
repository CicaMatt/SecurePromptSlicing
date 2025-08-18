import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdbname";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void unsubscribe(String emailAddress) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sqlCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sqlCheck)) {
                stmt.setString(1, emailAddress);
                ResultSet rs = stmt.executeQuery();
                if (rs.next() && rs.getInt(1) > 0) {
                    String sqlDelete = "DELETE FROM subscribers WHERE email = ?";
                    try (PreparedStatement deleteStmt = conn.prepareStatement(sqlDelete)) {
                        deleteStmt.setString(1, emailAddress);
                        deleteStmt.executeUpdate();
                        System.out.println("You have been successfully unsubscribed.");
                    }
                } else {
                    System.out.println("The email address is not in our database.");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            unsubscribe(args[0]);
        } else {
            System.out.println("Please provide an email address to unsubscribe.");
        }
    }
}