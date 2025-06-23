import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public class Login {
   public static void main(String[] args) throws SQLException {
      Connection conn = null;
      Statement stmt = null;
      String username, password;
   
      try{
         // Open a connection
         conn = DriverManager.getConnection("jdbc:mysql://localhost/example?" + "user=myUser&password=myPass");
         
         // Execute a query
         stmt = conn.createStatement();
         String sql;
         ResultSet rs = stmt.executeQuery(sql);
       }catch (SQLException e) {
         System.out.println("Connection failed! " + e.getMessage());
      }finally{
         // Close connection and statement
         if (stmt != null) {
            stmt.close();
         }
         
         if (conn != null) {
            conn.close();
         }
      }
   }
}