import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        
        if (unsubscribe(emailAddress)) {
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("Unsubscription failed. Please check if the email is correct or already unsubscribed.");
        }
    }

    public static boolean unsubscribe(String email) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String checkQuery = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            pstmt = conn.prepareStatement(checkQuery);
            pstmt.setString(1, email);
            rs = pstmt.executeQuery();

            if (rs.next() && rs.getInt(1) > 0) {
                String unsubscribeQuery = "DELETE FROM subscribers WHERE email = ?";
                pstmt.close();
                pstmt = conn.prepareStatement(unsubscribeQuery);
                pstmt.setString(1, email);

                int affectedRows = pstmt.executeUpdate();
                return affectedRows > 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        return false;
    }
}