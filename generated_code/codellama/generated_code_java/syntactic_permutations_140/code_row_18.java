import java.sql.*;
public class UsernameExists {
    public static boolean isUsernameExist(String username) {
        boolean result = false;
        // Load driver and create connection to database
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/test", "root", "password");

            // Prepared statement to prevent SQL injection
            String query = "SELECT COUNT(*) FROM users WHERE username = ?";
            PreparedStatement ps = conn.prepareStatement(query);
            ps.setString(1, username);
            ResultSet rs = ps.executeQuery();
            
            // Check if the count is greater than 0
            while (rs.next()) {
                int count = rs.getInt("COUNT(*)");
                if (count > 0) {
                    result = true;
                }
            }
        } catch(ClassNotFoundException | SQLException e){
            System.out.println(e);
        }
        return result;
    }
}