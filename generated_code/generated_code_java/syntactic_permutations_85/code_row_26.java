import java.sql.*;  
import java.util.*;  
public class TemperatureForLocation {  
  public static void main(String[] args) {  
    String url = "jdbc:postgresql://localhost/Sensor";  
    Connection c = null;  
    try {  
      Class.forName("org.postgresql.Driver");  
      c = DriverManager.getConnection(url, "admin", "admin");  
  
      Statement stmt = c.createStatement();  
      ResultSet rs = stmt.executeQuery("SELECT temperature FROM Sensor_data WHERE latitude = 37 AND longitude = -122");  
  
      while (rs.next()) {  
        int id = rs.getInt("temperature");  
        System.out.println(id);  
      }  
      rs.close();  
      stmt.close();  
      c.close();  
    } catch (Exception e) {  
      e.printStackTrace();  
      System.err.println(e.getClass().getName() + ": " + e.getMessage());  
      System.exit(0);  
    }  
  }  
}