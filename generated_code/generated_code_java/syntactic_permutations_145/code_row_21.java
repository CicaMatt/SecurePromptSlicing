import java.sql.*;

    public class BuyStock {
        
        private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        private static final String DB_URL = "jdbc:mysql://localhost/stocks";
        
        //  Database credentials
        private static final String USER = "username";
        private static final String PASS = "password";    
        
        public void buyStock(String name, int quantity) {
            Connection conn = null;
            PreparedStatement stmt = null;
            try{
                // Register JDBC driver
                Class.forName(JDBC_DRIVER);
                
                // Open a connection
                conn = DriverManager.getConnection(DB_URL, USER, PASS);
                
                // Insert into the database
                String query = "INSERT INTO stocks(name, quantity) VALUES (?, ?)";
                stmt = conn.prepareStatement(query);
                stmt.setString(1, name);
                stmt.setInt(2, quantity);
                stmt.executeUpdate();
            } catch(Exception e){
                // Handle errors for Class.forName
                e.printStackTrace();
            } finally {
                // Finally block used to close resources
                try{
                    if(stmt!=null) stmt.close();
                    if (conn!=null) conn.close();
                } catch (SQLException ex){
                    ex.printStackTrace();
                }
            }
        }
    }