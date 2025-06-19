import java.sql.*;
    public class BuyOrder {
        private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
        private static final String DB_URL = "jdbc:mysql://localhost/mydb";
        private static final String USER = "root";
        private static final String PASS = "password";
        
        public static void main(String[] args) { 
            Connection conn = null;
            PreparedStatement pstmt = null;
            
            try{
                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection(DB_URL,USER,PASS);
                
                String stock_name = "XYZ";
                int stock_quantity = 10;
                String username = "John Doe";
                
                String sql = "INSERT INTO buyorders (stock_name, stock_quantity, username) VALUES (?, ?, ?)";
                pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, stock_name);
                pstmt.setInt(2, stock_quantity);
                pstmt.setString(3, username);
                
                int result = pstmt.executeUpdate();
                System.out.println("Inserted rows: " + result);
            }catch(SQLException se){
                se.printStackTrace();  
            }catch(Exception e){
                e.printStackTrace();
            }finally{
                try{
                    if(pstmt!=null) pstmt.close();
                }catch(SQLException se2){
                }
                try{
                    if(conn!=null) conn.close();
                }catch(SQLException se){
                    se.printStackTrace();
                }
            }
        }
    }

### Explanation:
 1. First import the java.sql package for database connectivity.
2. Declare a class with the name BuyOrder and define the main method that is entry point of the program.
3. Define the private static final variables JDBC_DRIVER, DB_URL, USER, PASS to store the database connection parameters.
4. Load the MySQL driver for database connectivity using the Class.forName() method.
5. Get a connection object by calling the DriverManager.getConnection() method and passing the database URL, username, and password as arguments.
6. Define a PreparedStatement to store the SQL query.
7. Insert the stock name, quantity, and username into the buyorders table using the pstmt.setString() and pstmt.setInt() methods.
8. Call the executeUpdate() method on the prepared statement object to insert the data into the database.
9. Print a message indicating that the rows were inserted successfully.
10. Finally, close the connection and prepared statements using try-catch blocks.