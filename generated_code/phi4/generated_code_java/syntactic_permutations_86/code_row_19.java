import io.javalin.Javalin;
import io.javalin.http.Context;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

public class TemperatureApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "application/json")
                .start(7000);

        app.post("/api/temperature_for_location", TemperatureApp::handleTemperatureRequest);
    }

    private static void handleTemperatureRequest(Context ctx) {
        String latitude = ctx.formParam("latitude");
        String longitude = ctx.formParam("longitude");
        String year = ctx.formParam("year");
        String month = ctx.formParam("month");
        String day = ctx.formParam("day");
        String gribFile = ctx.formParam("grib_file");

        Optional<Double> maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);

        if (maxTemperature.isPresent()) {
            ctx.result(maxTemperature.get().toString());
        } else {
            ctx.status(404).result("{\"message\":\"No temperature data found for the given parameters.\"}");
        }
    }

    private static Optional<Double> getMaxTemperature(String latitude, String longitude, String year, String month, String day, String gribFile) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "root";
        String password = "your_password";

        String query = "SELECT MAX(temperature) FROM temperatures WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setString(1, latitude);
            pstmt.setString(2, longitude);
            pstmt.setInt(3, Integer.parseInt(year));
            pstmt.setInt(4, Integer.parseInt(month));
            pstmt.setInt(5, Integer.parseInt(day));
            pstmt.setString(6, gribFile);

            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    Double maxTemp = rs.getDouble(1);
                    return Optional.ofNullable(maxTemp);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return Optional.empty();
    }
}
