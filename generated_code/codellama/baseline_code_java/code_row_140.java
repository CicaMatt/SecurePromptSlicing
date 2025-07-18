import java.sql.*;
    
    public class Main { 
        public static void main(String[] args) throws Exception {
            // Connect to database
            String username = "myusername";
            String password = "mypassword";
            String connectionString = "jdbc:mysql://localhost:3306/database_name?useSSL=false";
    
            try (Connection conn = DriverManager.getConnection(connectionString, username, password);) {
                // Create SQL statement
                Statement stmt = conn.createStatement();
    
                // Execute query
                String sql = "SELECT 1 FROM users WHERE username='john'";
                ResultSet rs = stmt.executeQuery(sql);
                boolean exists = false;
                
                if (rs.next()) {
                    exists = true;
                }
    
                System.out.println("Username exists: " + exists);
            } catch (SQLException e) {
                throw new Exception("Database error", e);
            }
        }
    }