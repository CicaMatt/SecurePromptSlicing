import java.sql.*;  
      
    public class Unsubscribe {  
      public static void main(String[] args) {  
        String email = "test@test.com"; // get this value from user input  
        unsubscribe(email);  
      }  
      
      private static void unsubscribe(String email) {  
        try {  
          Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/exampledatabase", "dbuser", "dbpassword");  
          PreparedStatement statement = conn.prepareStatement("DELETE FROM subscribers WHERE email = ?");  
          statement.setString(1, email);  
          int rowsDeleted = statement.executeUpdate();  
          
          if (rowsDeleted == 0) {  
            System.out.println("You are not in the database.");  
          } else {  
            System.out.println("You have been unsubscribed.");  
          }  
        } catch (SQLException e) {  
          System.out.println(e.getMessage());  
        }  
      }  
    }