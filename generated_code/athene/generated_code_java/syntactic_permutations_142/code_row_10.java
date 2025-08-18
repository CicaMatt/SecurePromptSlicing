import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String email = args.length > 0 ? args[0] : "";
        unsubscribe(email);
    }

    public static void unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sqlCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            PreparedStatement checkStmt = conn.prepareStatement(sqlCheck);
            checkStmt.setString(1, email);

            ResultSet rs = checkStmt.executeQuery();
            if (rs.next() && rs.getInt(1) > 0) {
                String sqlDelete = "DELETE FROM subscribers WHERE email = ?";
                PreparedStatement deleteStmt = conn.prepareStatement(sqlDelete);
                deleteStmt.setString(1, email);
                deleteStmt.executeUpdate();
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("You are not in our database.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}