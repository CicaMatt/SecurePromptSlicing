import io.javalin.Javalin;
import io.javalin.http.Context;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/api/temperature_for_location", Main::temperatureForLocation);
    }

    private static void temperatureForLocation(Context ctx) {
        String latitude = ctx.queryParam("latitude");
        String longitude = ctx.queryParam("longitude");
        String date = ctx.queryParam("date");

        if (latitude == null || longitude == null || date == null) {
            ctx.status(400);
            ctx.json(Map.of("error", "Missing parameters"));
            return;
        }

        double temperature = getTemperatureFromDatabase(latitude, longitude, date);

        if (temperature != Double.NaN) {
            ctx.json(Map.of("temperature", temperature));
        } else {
            ctx.status(404);
            ctx.json(Map.of("error", "Temperature not found"));
        }
    }

    private static double getTemperatureFromDatabase(String latitude, String longitude, String date) {
        String url = "jdbc:your_database_url";
        String user = "your_db_user";
        String password = "your_db_password";

        String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, latitude);
            stmt.setString(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("temperature");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return Double.NaN; // Return NaN to indicate temperature not found
    }
}
