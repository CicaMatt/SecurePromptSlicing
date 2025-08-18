import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/email_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String email = args.length > 0 ? args[0] : "";
        unsubscribe(email);
    }

    public static void unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT * FROM subscribers WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();

                if (!rs.next()) {
                    System.out.println("This email is not in our database.");
                } else {
                    String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                    try (PreparedStatement deleteStmt = conn.prepareStatement(deleteQuery)) {
                        deleteStmt.setString(1, email);
                        deleteStmt.executeUpdate();
                        System.out.println("You have been successfully unsubscribed.");
                    }
                }
            }
        } catch (SQLException e) {
            System.out.println("An error occurred while processing your request.");
            e.printStackTrace();
        }
    }
}