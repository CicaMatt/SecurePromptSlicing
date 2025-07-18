import java.sql.*; 

public class CheckUser{
   public static void main(String[] args) {
      String url = "jdbc:mysql://localhost/userdb";
      String user = "username";
      String password = "password";
      try (Connection conn = DriverManager.getConnection(url, user, password); 
         Statement stmt = conn.createStatement();) {
         // Execute the query and get results
            ResultSet rs = stmt.executeQuery("SELECT username FROM users WHERE username='username'");
             if (rs.next()) {
                 System.out.println(true); 
                } else {
                   System.out.println(false);
                    }
         // Clean up and close resources
            rs.close(); stmt.close(); conn.close();
      } catch (SQLException e) {
          throw new IllegalStateException("Cannot connect to the database!", e);
        } 
   }
}