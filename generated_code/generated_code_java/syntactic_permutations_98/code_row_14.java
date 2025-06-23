import java.sql.*;
    public class Register {

        private Connection conn;
        private PreparedStatement pstmt;
        
        public Register() throws SQLException {
            String url = "jdbc:mysql://localhost/test";
            conn = DriverManager.getConnection(url, "root", "");
        }
    
        public void registerUser(String username, String password) throws SQLException {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?);"
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, password);
            pstmt.executeUpdate();
        }
    
        public static void main(String[] args) {
            try {
                Register register = new Register();
                register.registerUser("example", "pass123");
            } catch (SQLException e) {
                System.out.println(e.getMessage());
            }
        }
    }