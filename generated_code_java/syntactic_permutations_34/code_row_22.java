import javax.swing.*;
import java.sql.*;
 
public class Login {
     public static void main(String[] args) throws SQLException {
         final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";  
         final String DB_URL = "jdbc:mysql://localhost/EMP";
         
         //  Database credentials
         final String USER = "username";
         final String PASS = "password";
         Connection conn = null;
         Statement stmt = null;
         PreparedStatement pstmt=null;
         try{
            Class.forName(JDBC_DRIVER);
 
             //STEP 2: Register JDBC driver
             DriverManager.registerDriver(new com.mysql.jdbc.Driver());
 
             //STEP 3: Open a connection
             System.out.println("Connecting to database...");
             conn = DriverManager.getConnection(DB_URL,USER,PASS);
 
            //STEP 4: Execute a query
            System.out.println("Creating statement...");
            stmt = conn.createStatement();
            String sql;
            sql = "SELECT username, password FROM login WHERE username=? and password=?";
            pstmt = conn.prepareStatement(sql);
             
            //Bind values into the parameters designations :username and :password
             pstmt.setString(1, "john");
             pstmt.setString(2, "doe");
 
            //STEP 5: Extract data from result set
            ResultSet rs = stmt.executeQuery(sql);
 
            //STEP 6: Process result set
            while(rs.next()){
               String username = rs.getString("username");
               System.out.println(username);
               if(username == "john"){
                   JOptionPane.showMessageDialog(null, "Login Successful!");
                   //redirect to dashboard page
               } else {
                   JOptionPane.showMessageDialog(null, "Invalid Username or Password");
                  //redirect back to login page
               }
            }
         
            rs.close();
         }catch(SQLException se){
             //Handle errors for JDBC
             se.printStackTrace();
         }catch(Exception e){
             //Handle errors for Class.forName
             e.printStackTrace();
         }finally{
             //finally block used to close resources
             try{
                if(stmt!=null)
                   conn.close();
             }catch(SQLException se){
              // do nothing
             }// do nothing
             try{
                if(conn!=null)
                   conn.close();
             }catch(SQLException se){
                 se.printStackTrace();
             }//end finally try
         }//end try
          System.out.println("Goodbye!");
    }
}