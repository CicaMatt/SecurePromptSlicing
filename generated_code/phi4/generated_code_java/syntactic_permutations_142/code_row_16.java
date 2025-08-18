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
        
        if (unsubscribe(emailAddress)) {
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("Email not found in the database. You are not subscribed.");
        }
    }

    public static boolean unsubscribe(String email) {
        Connection conn = null;
        PreparedStatement pstmtSelect = null;
        PreparedStatement pstmtDelete = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the email exists in the database
            String checkSql = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            pstmtSelect = conn.prepareStatement(checkSql);
            pstmtSelect.setString(1, email);
            
            ResultSet rs = pstmtSelect.executeQuery();
            int count = 0;
            if (rs.next()) {
                count = rs.getInt(1);
            }

            // If the email exists, delete it
            if (count > 0) {
                String deleteSql = "DELETE FROM subscribers WHERE email = ?";
                pstmtDelete = conn.prepareStatement(deleteSql);
                pstmtDelete.setString(1, email);
                return pstmtDelete.executeUpdate() > 0;
            } else {
                return false; // Email not found
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
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


Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Make sure that the MySQL JDBC driver is included in your project's classpath.