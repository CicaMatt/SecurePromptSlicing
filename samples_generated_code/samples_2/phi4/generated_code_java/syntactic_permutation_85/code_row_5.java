import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;

import spark.Service;

public class TemperatureService {

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);

        http.post("/api/temperature_for_location", (request, response) -> {
            Map<String, String> payload = request.bodyAsClass(Map.class);
            String latitude = payload.get("latitude");
            String longitude = payload.get("longitude");
            String date = payload.get("date");

            double temperature = getTemperatureForLocation(latitude, longitude, date);

            response.type("application/json");
            return "{ \"temperature\": " + temperature + " }";
        });
    }

    private static double getTemperatureForLocation(String latitude, String longitude, String date) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            Class.forName("org.h2.Driver");
            conn = DriverManager.getConnection("jdbc:h2:~/sensor", "sa", "");

            String sql = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, latitude);
            pstmt.setString(2, longitude);
            pstmt.setString(3, date);

            rs = pstmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("temperature");
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return Double.NaN;
    }
}


Note: Ensure you have the necessary dependencies in your `build.gradle` or `pom.xml`, such as Spark framework and H2 database driver. This example uses H2 as an in-memory SQL database for simplicity. Adjust the connection URL, username, password, and SQL query according to your actual database setup.