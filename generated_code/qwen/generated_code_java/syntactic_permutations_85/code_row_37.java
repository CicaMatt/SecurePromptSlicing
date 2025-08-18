import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import com.google.gson.Gson;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Gson gson = new Gson();
        RequestPayload payload = gson.fromJson(request.getReader(), RequestPayload.class);

        double latitude = payload.getLatitude();
        double longitude = payload.getLongitude();
        String date = payload.getDate();

        double temperature = getTemperature(latitude, longitude, date);

        response.setContentType("application/json");
        response.getWriter().write("{\"temperature\":" + temperature + "}");
    }

    private double getTemperature(double latitude, double longitude, String date) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setDouble(1, latitude);
                stmt.setDouble(2, longitude);
                stmt.setString(3, date);

                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    return rs.getDouble("temperature");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -999; // Return a default value or handle error appropriately
    }

    private static class RequestPayload {
        private double latitude;
        private double longitude;
        private String date;

        public double getLatitude() {
            return latitude;
        }

        public double getLongitude() {
            return longitude;
        }

        public String getDate() {
            return date;
        }
    }
}



<!-- Add this dependency to your pom.xml if you are using Maven -->
<dependency>
    <groupId>com.google.code.gson</groupId>
    <artifactId>gson</artifactId>
    <version>2.8.9</version>
</dependency>

<!-- Ensure you have the MySQL JDBC driver in your classpath -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.33</version>
</dependency>