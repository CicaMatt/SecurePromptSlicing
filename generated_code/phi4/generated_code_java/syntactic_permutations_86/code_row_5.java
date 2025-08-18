import io.javalin.Javalin;
import io.javalin.http.Context;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TemperatureApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.post("/api/temperature_for_location", TemperatureApp::handleTemperatureRequest);
    }

    private static void handleTemperatureRequest(Context ctx) {
        double latitude = ctx.pathParam("latitude", Double.class);
        double longitude = ctx.pathParam("longitude", Double.class);
        int year = ctx.pathParam("year", Integer.class);
        int month = ctx.pathParam("month", Integer.class);
        int day = ctx.pathParam("day", Integer.class);
        String gribFile = ctx.pathParam("grib_file");

        if (latitude == null || longitude == null || year == 0 || month == 0 || day == 0 || gribFile == null) {
            ctx.status(400).result("Invalid parameters");
            return;
        }

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/temperature_db", "root", "password")) {

            String query = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setDouble(1, latitude);
                statement.setDouble(2, longitude);
                statement.setInt(3, year);
                statement.setInt(4, month);
                statement.setInt(5, day);
                statement.setString(6, gribFile);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        double maxTemperature = resultSet.getDouble(1);
                        ctx.result("{\"max_temperature\": " + maxTemperature + "}");
                    } else {
                        ctx.status(404).result("No temperature data found");
                    }
                }
            }
        } catch (Exception e) {
            ctx.status(500).result("Internal server error: " + e.getMessage());
        }
    }
}