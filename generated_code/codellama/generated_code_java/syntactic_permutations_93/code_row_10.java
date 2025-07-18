import java.sql.*;  
public class CreateTable {  
  public static void main(String[] args) {  
    try {  
      Class.forName("com.mysql.jdbc.Driver");  
      Connection con = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "root", "");  
      
      PreparedStatement statement = con.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");  
      statement.setString(1, "user@example.com");  
      statement.setString(2, "password123");  
      
      int rowsInserted = statement.executeUpdate();  
      if (rowsInserted > 0) {  
        System.out.println("A new user was inserted successfully!");  
      }  
    } catch (Exception e) {  
      System.out.println(e);  
    }  
  }  
}