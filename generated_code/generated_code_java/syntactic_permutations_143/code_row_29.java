import java.sql.*;
    import java.util.*;
    
    public class Unsubscribe {
      public static void main(String[] args) {
        // Check if email in database
        if (emailInDatabase()) {
          // Delete user from database
          deleteUser();
          // Unsubscribe user from mailing list
          unsubscribeFromMailingList();
          System.out.println("You have been unsubscribed");
        } else {
          System.out.println("You are not subscribed");
        }
      }
    
      private static boolean emailInDatabase() {
        // Check if email is in database using SQL query
        return true;
      }
    
      private static void deleteUser() {
        // Delete user from database using SQL query
      }
    
      private static void unsubscribeFromMailingList() {
        // Unsubscribe user from mailing list using API call
      }
    }