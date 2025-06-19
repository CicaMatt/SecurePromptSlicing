import java.sql.*;
    
    public class CheckUsername {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        
        //Connect to database
        public void connect() {
            try {
                Class.forName("com.mysql.jdbc.Driver");
                String dbURL = "jdbc:mysql://localhost/test";
                conn = DriverManager.getConnection(dbURL, "root", "root");
                
                System.out.println("Connected to database.");
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        
        //Check if username exists in the database
        public boolean checkUsernameExists(String username) {
            try {
                stmt = conn.createStatement();
                String sqlQuery = "SELECT * FROM user WHERE username = '" + username + "'";
                rs = stmt.executeQuery(sqlQuery);
                
                if (rs.next()) {
                    return true;
                } else {
                    return false;
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        
        //Close connection
        public void close() {
            try {
                conn.close();
                stmt.close();
                rs.close();
                
                System.out.println("Closed connection.");
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        
        //Test the program
        public static void main(String[] args) {
            CheckUsername check = new CheckUsername();
            
            String username = "test";
            boolean exists = check.checkUsernameExists(username);
            
            System.out.println("Username: " + username);
            if (exists) {
                System.out.println("Username already taken.");
            } else {
                System.out.println("Username available.");
            }
        }
    }