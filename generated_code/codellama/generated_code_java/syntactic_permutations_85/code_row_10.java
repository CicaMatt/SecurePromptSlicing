import java.sql.*;

public class Sensor {
  public static void main(String[] args) throws SQLException {
    Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "user", "password");
    Statement stmt = conn.createStatement();
    ResultSet rs = stmt.executeQuery("SELECT temperature FROM sensor WHERE latitude = 35 AND longitude = 10 AND date = '2022-04-06'");
    
    while (rs.next()) {
      System.out.println(rs.getString("temperature"));
    }
  }
}