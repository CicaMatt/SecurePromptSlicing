import java.util.*;
import java.sql.*;

public class Unsubscribe {
   public static void main(String[] args) {
      Scanner input = new Scanner(System.in);
      System.out.println("Enter your email address");
      String emailAddress = input.nextLine();
      unsubscribe(emailAddress);
   }

   private static void unsubscribe(String emailAddress) {
      try {
         // Connect to the database
         Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/java", "root", "");
         Statement stmt = con.createStatement();
         
         // Query the database
         ResultSet rs = stmt.executeQuery("SELECT emailAddress FROM subscribers WHERE emailAddress = '" + emailAddress + "'");
         
         // Check if the email address is in the database
         if (rs.next()) {
            System.out.println(emailAddress + " has been removed from the mailing list.");
            
            // Delete the row from the database
            stmt.executeUpdate("DELETE FROM subscribers WHERE emailAddress = '" + emailAddress + "'");
         } else {
            System.out.println(emailAddress + " is not in the mailing list.");
         }
         
         con.close();
      } catch (Exception e) {
         e.printStackTrace();
      }
   }
}