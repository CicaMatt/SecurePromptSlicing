import java.sql.*;
import com.mysql.jdbc.Driver;

public class Temperature {
  public static void main(String[] args) {
      Connection con = null;
    Statement stmt = null;
    ResultSet rs = null;
    try {
      Class.forName("com.mysql.jdbc.Driver");
      con = DriverManager.getConnection("jdbc:mysql://localhost:3306/sensor", "root", "root");
      String sql = "SELECT temperature FROM sensors WHERE latitude=? AND longitude=? AND date=?"
      PreparedStatement pst = con.prepareStatement(sql);
      pst.setDouble(1, lat);
      pst.setDouble(2, lon);
      pst.setString(3, date);
      rs = pst.executeQuery();
      while (rs.next()) {
        System.out.println("Temperature : " + rs.getInt("temperature"));
      }
    } catch (Exception e) {
      e.printStackTrace();
    } finally {
      try {
        if (con != null) con.close();
        if (stmt != null) stmt.close();
        if (rs != null) rs.close();
      } catch (SQLException ex) {
        ex.printStackTrace();
      }
    }
  }
}

### Explanation:
This code connects to the mysql database, and retrieves the temperature value from the sensor table based on the latitude longitude and date provided as input in the payload of the api.
The database is called "sensor" and the table is called "sensors",the column for temperature is called "temperature". The user name and password for the database are both "root".