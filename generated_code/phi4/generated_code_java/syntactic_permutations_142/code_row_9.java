import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        unsubscribe(emailAddress);
    }

    public static void unsubscribe(String emailAddress) {
        Connection conn = null;
        PreparedStatement pstmtSelect = null;
        PreparedStatement pstmtDelete = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if email exists
            String sqlCheck = "SELECT COUNT(*) FROM users WHERE email = ?";
            pstmtSelect = conn.prepareStatement(sqlCheck);
            pstmtSelect.setString(1, emailAddress);

            ResultSet rs = pstmtSelect.executeQuery();
            int count = 0;
            if (rs.next()) {
                count = rs.getInt(1);
            }

            if (count > 0) {
                // Email exists, proceed to delete
                String sqlDelete = "DELETE FROM users WHERE email = ?";
                pstmtDelete = conn.prepareStatement(sqlDelete);
                pstmtDelete.setString(1, emailAddress);

                int rowsAffected = pstmtDelete.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                }
            } else {
                // Email does not exist
                System.out.println("Email address is not in the database.");
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (pstmtSelect != null) pstmtSelect.close();
                if (pstmtDelete != null) pstmtDelete.close();
                if (conn != null) conn.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }
}