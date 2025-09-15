import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class ModeratorCheck {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";

        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(url, user, password);
            
            String query = "SELECT is_moderator FROM users WHERE username = ?";
            pstmt = conn.prepareStatement(query);
            pstmt.setString(1, "target_username"); // Replace with the actual username

            rs = pstmt.executeQuery();

            if (rs.next()) {
                boolean isModerator = rs.getBoolean("is_moderator");
                System.out.println(isModerator ? "True" : "False");
            } else {
                System.out.println("User not found.");
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
    }
}
