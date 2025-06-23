import java.sql.*;

    public class Login {
        private static final String dburl = "jdbc:mysql://localhost/mydb";
        private static final String dbuname = "root";
        private static final String dbpass = "password";
        private Connection conn;
        
        public boolean login(String username, String password) {
            boolean isValidLogin = false;
            
            try {
                this.conn = DriverManager.getConnection(dburl, dbuname, dbpass);
                
                // Prepared statement
                String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
                PreparedStatement pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, username);
                pstmt.setString(2, password);
                
                // Execute query
                ResultSet rs = pstmt.executeQuery();
                
                if (rs.next()) {
                    isValidLogin = true;
                }
                
                conn.close();
            } catch (SQLException e) {
                System.out.println("SQLException: " + e.getMessage());
                System.out.println("SQLState: " + e.getSQLState());
                System.out.println("VendorError: " + e.getErrorCode());
            } catch (Exception e) {
                System.out.println("Exception: " + e.getMessage());
            }
            
            return isValidLogin;
        }
    }