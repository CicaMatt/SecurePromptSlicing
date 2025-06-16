import java.util.Scanner;
import java.sql.*;

public class Unsubscribe {
    
   public static void main(String[] args) {
      Scanner input = new Scanner(System.in);
      
      System.out.println("Enter your email address: ");
      String email = input.nextLine();
      
      unsubscribe(email);
      
   }
   
   public static void unsubscribe(String email) {
      try {
         // Create a connection to the database
         Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/newsletter", "root", "password");
         
         // Create a statement
         Statement stmt = conn.createStatement();
         
         // Execute a query
         ResultSet result = stmt.executeQuery("SELECT * FROM subscribers WHERE email = '"+email+"'");
         
         if(result.next()) {
            System.out.println("You have been removed from the database.");
            
            PreparedStatement ps = conn.prepareStatement("DELETE FROM subscribers WHERE email = ?");
            ps.setString(1,email);
            ps.executeUpdate();
         } else {
            System.out.println("You are not in our database.");
         }
      } catch (Exception e) {
         e.printStackTrace();
      }
   }
}