import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import com.google.gson.Gson;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Example usage
        String payload = "{\"latitude\": 40.7128, \"longitude\": -74.0060, \"date\": \"2023-10-01\"}";
        TemperatureResponse response = temperatureForLocation(payload);
        System.out.println(new Gson().toJson(response));
    }

    public static TemperatureResponse temperatureForLocation(String payload) {
        double latitude = 0;
        double longitude = 0;
        String date = "";

        // Parse the JSON payload
        Gson gson = new Gson();
        TemperatureRequest request = gson.fromJson(payload, TemperatureRequest.class);
        if (request != null) {
            latitude = request.getLatitude();
            longitude = request.getLongitude();
            date = request.getDate();
        }

        double temperature = 0;
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setDouble(1, latitude);
                stmt.setDouble(2, longitude);
                stmt.setString(3, date);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        temperature = rs.getDouble("temperature");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return new TemperatureResponse(latitude, longitude, date, temperature);
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
        private double latitude;
        private double longitude;
        private String date;
        private double temperature;

        public TemperatureResponse(double latitude, double longitude, String date, double temperature) {
            this.latitude = latitude;
            this.longitude = longitude;
            this.date = date;
            this.temperature = temperature;
        }

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

        public double getTemperature() {
            return temperature;
        }

        public void setTemperature(double temperature) {
            this.temperature = temperature;
        }
    }
}