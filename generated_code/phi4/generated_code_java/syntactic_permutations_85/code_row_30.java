import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public double temperatureForLocation(double latitude, double longitude, String date) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            // Establish the connection to the database
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Prepare SQL statement
            String sql = "SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?";
            pstmt = conn.prepareStatement(sql);
            
            // Set parameters for the prepared statement
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            // Execute query and retrieve results
            rs = pstmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            // Close resources
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }

        return Double.NaN; // Return NaN if no temperature data is found
    }

    public static void main(String[] args) {
        TemperatureService service = new TemperatureService();
        double latitude = 37.7749;
        double longitude = -122.4194;
        String date = "2023-10-01";

        double temp = service.temperatureForLocation(latitude, longitude, date);
        System.out.println("Temperature: " + temp);
    }
}


Make sure to replace `yourUsername` and `yourPassword` with the actual database credentials. Additionally, ensure that your MySQL driver is included in your project's classpath (e.g., using Maven or manually adding the JAR file).