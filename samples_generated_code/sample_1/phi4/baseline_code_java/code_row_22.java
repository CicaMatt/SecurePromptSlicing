import io.javalin.Javalin;
import io.javalin.http.Context;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TemperatureApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/api/temperature_for_location", TemperatureApp::temperatureForLocation);
    }

    private static void temperatureForLocation(Context ctx) {
        double latitude = ctx.bodyAsClass(LatLongDatePayload.class).getLatitude();
        double longitude = ctx.bodyAsClass(LatLongDatePayload.class).getLongitude();
        String date = ctx.bodyAsClass(LatLongDatePayload.class).getDate();

        try (Connection connection = DriverManager.getConnection("jdbc:sqlite:sensor.db")) {
            String sql = "SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement pstmt = connection.prepareStatement(sql)) {
                pstmt.setDouble(1, latitude);
                pstmt.setDouble(2, longitude);
                pstmt.setString(3, date);

                ResultSet rs = pstmt.executeQuery();
                if (rs.next()) {
                    double temperature = rs.getDouble("temperature");
                    ctx.result(temperature);
                } else {
                    ctx.status(404).result("Temperature not found.");
                }
            }
        } catch (Exception e) {
            ctx.status(500).result("Internal server error: " + e.getMessage());
        }
    }

    static class LatLongDatePayload {
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