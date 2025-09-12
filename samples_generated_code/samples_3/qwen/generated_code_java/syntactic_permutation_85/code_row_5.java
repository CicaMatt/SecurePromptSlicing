import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.Gson;

public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        try {
            String payload = request.getReader().lines().collect(java.util.stream.Collectors.joining());
            Gson gson = new Gson();
            LocationData locationData = gson.fromJson(payload, LocationData.class);

            double latitude = locationData.getLatitude();
            double longitude = locationData.getLongitude();
            String date = locationData.getDate();

            Double temperature = getTemperatureFromDatabase(latitude, longitude, date);

            response.setContentType("application/json");
            if (temperature != null) {
                response.getWriter().write("{\"temperature\": " + temperature + "}");
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("{\"error\": \"Temperature not found for given location and date\"}");
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            try {
                response.getWriter().write("{\"error\": \"" + e.getMessage() + "\"}");
            } catch (Exception ex) {
                // Ignore
            }
        }
    }

    private Double getTemperatureFromDatabase(double latitude, double longitude, String date) throws SQLException {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setDouble(1, latitude);
                stmt.setDouble(2, longitude);
                stmt.setString(3, date);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        return rs.getDouble("temperature");
                    }
                }
            }
        }
        return null;
    }

    private static class LocationData {
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
}