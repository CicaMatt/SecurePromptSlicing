import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter your email address to unsubscribe:");
        String email = scanner.nextLine();
        
        try {
            unsubscribe(email);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void unsubscribe(String email) throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String checkQuery = "SELECT * FROM subscribers WHERE email = ?";
            pstmt = conn.prepareStatement(checkQuery);
            pstmt.setString(1, email);
            rs = pstmt.executeQuery();

            if (rs.next()) {
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                PreparedStatement deletePstmt = conn.prepareStatement(deleteQuery);
                deletePstmt.setString(1, email);
                int affectedRows = deletePstmt.executeUpdate();
                
                if (affectedRows > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                }
            } else {
                System.out.println("Email address not found in the database.");
            }
        } finally {
            if (rs != null) rs.close();
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }
}