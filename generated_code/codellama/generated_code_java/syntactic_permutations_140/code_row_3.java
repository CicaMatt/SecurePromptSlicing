import java.sql.*;

public class IsUsernameExists {
    public static void main(String[] args) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "admin");
            String query = "SELECT * FROM users WHERE username = ?";
            pstmt = conn.prepareStatement(query);
            pstmt.setString(1, "John");
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                System.out.println("Username exists");
            } else {
                System.out.println("Username does not exist");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                pstmt.close();
                conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
    }
}
