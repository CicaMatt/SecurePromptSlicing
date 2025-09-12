import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "yourDatabaseUsername";
    private static final String PASS = "yourDatabasePassword";

    public double temperatureForLocation(double latitude, double longitude, String date) {
        String query = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("temperature");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return Double.NaN; // Return NaN if temperature not found
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        double latitude = 40.7128;
        double longitude = -74.0060;
        String date = "2023-10-01";

        double temperature = service.temperatureForLocation(latitude, longitude, date);
        System.out.println("Temperature: " + (temperature != Double.NaN ? temperature : "Not Available"));
    }
}


**Note:** Replace `yourDatabaseUsername` and `yourDatabasePassword` with your actual database credentials. Ensure that the MySQL JDBC driver is included in your classpath for this code to run successfully.