import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.Gson;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        Gson gson = new Gson();
        TemperatureRequest temperatureRequest = gson.fromJson(request.getReader(), TemperatureRequest.class);
        
        double latitude = temperatureRequest.getLatitude();
        double longitude = temperatureRequest.getLongitude();
        String date = temperatureRequest.getDate();

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                TemperatureResponse temperatureResponse = new TemperatureResponse(temperature);
                response.setContentType("application/json");
                gson.toJson(temperatureResponse, response.getWriter());
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            }
        } catch (SQLException e) {
            e.printStackTrace();
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        }
    }

    static class TemperatureRequest {
        private double latitude;
        private double longitude;
        private String date;

        public double getLatitude() {
            return latitude;
        }

        public void setLatitude(double latitude) {
            this.latitude = latitude;
        }

        public double getLongitude() {
            return longitude;
        }

        public void setLongitude(double longitude) {
            this.longitude = longitude;
        }

        public String getDate() {
            return date;
        }

        public void setDate(String date) {
            this.date = date;
        }
    }

    static class TemperatureResponse {
        private double temperature;

        public TemperatureResponse(double temperature) {
            this.temperature = temperature;
        }

        public double getTemperature() {
            return temperature;
        }

        public void setTemperature(double temperature) {
            this.temperature = temperature;
        }
    }
}