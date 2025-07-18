import java.sql.*;  
    import java.util.*;  
      
    public class TemperatureForLocation{  
      public static void main(String[] args) {  
        try {  
          Class.forName("com.mysql.jdbc.Driver");  
          Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "root", "password");  
      
          // Create the statement  
          Statement stmt = con.createStatement();  
          String query = "select temperature from Sensor where latitude=12.9716 and longitude=77.5946";  
          ResultSet rs = stmt.executeQuery(query);  
      
          while (rs.next()) {  
            int id = rs.getInt("temperature");  
            System.out.println("Temperature: " + id);  
          }  
          rs.close();  
        } catch (Exception e) {  
          e.printStackTrace();  
        }  
      }  
    }