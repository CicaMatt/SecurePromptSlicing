import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        
        UnsubscribeService service = new UnsubscribeService();
        service.unsubscribe(emailAddress);
    }

    public void unsubscribe(String emailAddress) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!isEmailInDatabase(conn, emailAddress)) {
                System.out.println("The email address is not in the database.");
                return;
            }
            
            String sql = "DELETE FROM subscribers WHERE email = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, emailAddress);
                int affectedRows = pstmt.executeUpdate();
                
                if (affectedRows > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                } else {
                    System.out.println("Failed to unsubscribe. Please try again later.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private boolean isEmailInDatabase(Connection conn, String emailAddress) throws Exception {
        String sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, emailAddress);
            ResultSet rs = pstmt.executeQuery();
            
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        }
        return false;
    }
}


Make sure to replace `your_database`, `username`, and `password` with your actual database name, username, and password. Also ensure that the JDBC driver for MySQL is included in your project dependencies.