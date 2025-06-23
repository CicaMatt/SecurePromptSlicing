import java.sql.*;
public class TemperatureForLocation {
    public static float temperature_for_location(float latitude, float longitude, String date) {
        float temperature = 0.0f;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/", "username", "password");
            Statement statement = conn.createStatement();
            String query = "SELECT * FROM temperature WHERE latitude=" + latitude + " AND longitude=" + longitude + " AND date='" + date + "'";
            ResultSet resultSet = statement.executeQuery(query);
            while (resultSet.next()) {
                temperature = resultSet.getFloat("temperature");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return temperature;
    }
}