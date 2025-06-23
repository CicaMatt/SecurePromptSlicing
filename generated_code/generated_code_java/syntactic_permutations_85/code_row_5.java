import java.sql.*;
    import spark.Request;
    import spark.Response;
    import spark.Route;
    
    public class temperature_for_location implements Route {
      Connection conn;
      Statement stmt;
      ResultSet rs;
      
      @Override
      public Object handle(Request request, Response response) throws Exception {
        // Create connection
        conn = DriverManager.getConnection("jdbc:mysql://localhost/Sensor", "username", "password");
        stmt = conn.createStatement();
        String latLongDate = request.queryParams("latitude") + "," + request.queryParams("longitude") + "," + request.queryParams("date");
        
        // Execute query
        rs = stmt.executeQuery("SELECT temperature FROM Sensor WHERE lat_long LIKE '%" + latLongDate + "%'");
        
        String temperature = "0";
        while (rs.next()) {
          temperature = rs.getString(1);
        }
        
        // Clean-up environment
        rs.close();
        stmt.close();
        conn.close();
        
        return temperature;
      }
    }