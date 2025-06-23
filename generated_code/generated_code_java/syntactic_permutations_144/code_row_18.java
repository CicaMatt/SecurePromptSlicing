import java.sql.*;
public class Email {
   public static void main(String[] args) {
      String email = "test@test.com";
      try {
         Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/database", "username", "password");
         Statement stmt = conn.createStatement();
         ResultSet rs = stmt.executeQuery("SELECT * FROM emails WHERE email = '"+email+"'");
         if (rs.next()) {
            System.out.println(1);
         } else {
            System.out.println(0);
         }
      } catch (Exception e) {
         System.err.println(e.getMessage());
      }
   }
}