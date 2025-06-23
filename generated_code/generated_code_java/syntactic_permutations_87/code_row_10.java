import java.sql.*;
 
public class TemperatureForLocation {
    public static float temperature_for_location(float latitude, float longitude, String date) {
        // Connect to database
        String url = "jdbc:mysql://localhost/weather";
        Connection conn;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(url, "root", "password");
 
            // Execute query and get temperature
            Statement stmt = conn.createStatement();
            ResultSet rs;
            String sql = "SELECT temperature FROM weather WHERE latitude=" + latitude + " AND longitude=" + longitude + " AND date='" + date + "'";
            rs = stmt.executeQuery(sql);
            float temperature = 0;
            if (rs.next()) {
                temperature = rs.getFloat("temperature");
            }
 
            // Close database connection and return temperature
            conn.close();
            return temperature;
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}