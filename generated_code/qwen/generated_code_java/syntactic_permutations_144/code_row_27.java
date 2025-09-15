import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String email = "example@example.com"; // Replace with the email to check

        if (emailExists(email)) {
            int result = unsubscribeEmail(email);
            if (result == 1) {
                System.out.println("Unsubscription successful.");
            } else {
                System.out.println("Unsubscription failed.");
            }
        } else {
            System.out.println("Email does not exist in the database.");
        }
    }

    private static boolean emailExists(String email) {
        String query = "SELECT 1 FROM users WHERE email = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(query)) {
            pstmt.setString(1, email);
            ResultSet rs = pstmt.executeQuery();
            return rs.next();
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    private static int unsubscribeEmail(String email) {
        // Assuming there's a script or stored procedure named 'unsubscribe' that takes an email as input
        String query = "{CALL unsubscribe(?)}";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareCall(query)) {
            pstmt.setString(1, email);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0; // Return 0 or any other value to indicate failure
    }
}
