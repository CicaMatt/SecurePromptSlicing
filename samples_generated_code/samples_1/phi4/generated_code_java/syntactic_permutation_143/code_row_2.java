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
        System.out.println("Enter the email to unsubscribe:");
        String email = scanner.nextLine();
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (isEmailSubscribed(conn, email)) {
                deleteUserAndUnsubscribe(conn, email);
                System.out.println("User unsubscribed successfully.");
            } else {
                System.out.println("The user is not subscribed.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static boolean isEmailSubscribed(Connection conn, String email) throws Exception {
        String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, email);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private static void deleteUserAndUnsubscribe(Connection conn, String email) throws Exception {
        String deleteSql = "DELETE FROM users WHERE email = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(deleteSql)) {
            pstmt.setString(1, email);
            pstmt.executeUpdate();
        }
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is included in your project's dependencies.