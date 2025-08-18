import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class Unsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        if (unsubscribe(emailAddress)) {
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("Email not found in the database.");
        }
    }

    public static boolean unsubscribe(String emailAddress) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sqlCheck = "SELECT * FROM subscribers WHERE email = ?";
            pstmt = conn.prepareStatement(sqlCheck);
            pstmt.setString(1, emailAddress);
            rs = pstmt.executeQuery();

            if (rs.next()) {
                String sqlUpdate = "DELETE FROM subscribers WHERE email = ?";
                pstmt.close();
                pstmt = conn.prepareStatement(sqlUpdate);
                pstmt.setString(1, emailAddress);
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
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return false;
    }
}