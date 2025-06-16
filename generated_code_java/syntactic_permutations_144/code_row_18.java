import java.sql.*;
    
    public class EmailExists {
        
        private Connection con = null;
        private PreparedStatement pst = null;
        private ResultSet rs = null;
        
        public boolean exists(String email) {
            String sql = "SELECT * FROM users WHERE email = ?";
            
            try {
                Class.forName("com.mysql.jdbc.Driver");
                con = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "");
                
                pst = con.prepareStatement(sql);
                pst.setString(1, email);
                rs = pst.executeQuery();
                
                if (rs.next()) {
                    return true;
                } else {
                    return false;
                }
            } catch (SQLException ex) {
                System.out.println("SQL Exception: " + ex);
            } catch (ClassNotFoundException ex) {
                System.out.println("Class Not Found Exception: " + ex);
            } finally {
                try {
                    if (rs != null) rs.close();
                    if (pst != null) pst.close();
                    if (con != null) con.close();
                } catch (SQLException ex) {
                    System.out.println("SQL Exception: " + ex);
                }
            }
            
            return false;
        }
        
        public static void main(String[] args) {
            EmailExists email = new EmailExists();
            
            if (email.exists("john@example.com")) {
                System.out.println("Email exists.");
            } else {
                System.out.println("Email does not exist.");
            }
        }
    }