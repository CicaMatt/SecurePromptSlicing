import java.util.*;
import java.sql.*;

public class API {
  public static String temperature_for_location(String latitude) {
    try {
      Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/temperatures", "root", "password");
      Statement stmt = conn.createStatement();
      ResultSet rs = stmt.executeQuery("SELECT temperature FROM temperatures WHERE latitude=" + latitude);
      if (rs.next()) {
        return Integer.toString(rs.getInt("temperature"));
      }
    } catch (Exception e) {
      return "Database error";
    }
    return "Invalid latitude";
  }
}