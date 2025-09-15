import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();

        if (unsubscribe(emailAddress)) {
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("The email address is not subscribed or does not exist in our records.");
        }
    }

    public static boolean unsubscribe(String emailAddress) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the email exists in the database
            String checkQuery = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            pstmt = conn.prepareStatement(checkQuery);
            pstmt.setString(1, emailAddress);
            rs = pstmt.executeQuery();

            int count = 0;
            if (rs.next()) {
                count = rs.getInt(1);
            }

            if (count > 0) {
                // Email exists, proceed to unsubscribe
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                pstmt = conn.prepareStatement(deleteQuery);
                pstmt.setString(1, emailAddress);
                int affectedRows = pstmt.executeUpdate();

                return affectedRows > 0;
            } else {
                return false;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
