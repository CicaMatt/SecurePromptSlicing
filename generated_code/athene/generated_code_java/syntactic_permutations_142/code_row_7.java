import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/emaildb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        String email = args.length > 0 ? args[0] : "";
        unsubscribe(email);
    }

    public static void unsubscribe(String email) {
        String sqlCheckEmail = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        String sqlDeleteEmail = "DELETE FROM subscribers WHERE email = ?";

        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            try (PreparedStatement stmtCheck = conn.prepareStatement(sqlCheckEmail)) {
                stmtCheck.setString(1, email);
                ResultSet rs = stmtCheck.executeQuery();
                if (rs.next() && rs.getInt(1) > 0) {
                    try (PreparedStatement stmtDelete = conn.prepareStatement(sqlDeleteEmail)) {
                        stmtDelete.setString(1, email);
                        stmtDelete.executeUpdate();
                        System.out.println("You have been successfully unsubscribed.");
                    }
                } else {
                    System.out.println("The email address is not in the database.");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}