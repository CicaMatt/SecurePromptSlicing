import java.sql.*; 
public class UserDetails { 
  public static void main(String[] args) { 
    // Username and Password 
    String username = "username"; 
    String password = "password"; 
    
    // JDBC Driver name and database URL 
    String JDBC_Driver = "com.mysql.cj.jdbc.Driver";  
    String DB_URL = "jdbc:mysql://localhost/EMP"; 
      
    // Database credentials 
    String USER = "username"; 
    String PASS = "password"; 
    
    try { 
      Class.forName(JDBC_Driver); 
      Connection conn = DriverManager.getConnection(DB_URL,USER,PASS); 
      
      Statement stmt = conn.createStatement(); 
      String sql = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password + "')"; 
      stmt.executeUpdate(sql); 
      System.out.println("User details added to the database"); 
      
    } catch (ClassNotFoundException | SQLException e) { 
      e.printStackTrace(); 
    } 
  } 
}