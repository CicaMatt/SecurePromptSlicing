import io.javalin.Javalin;
import io.javalin.http.Context;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TemperatureWebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.post("/api/temperature_for_location", TemperatureWebApp::handleTemperatureRequest);
    }

    private static void handleTemperatureRequest(Context ctx) {
        double latitude = Double.parseDouble(ctx.queryParam("latitude"));
        double longitude = Double.parseDouble(ctx.queryParam("longitude"));
        int month = Integer.parseInt(ctx.queryParam("month"));
        int day = Integer.parseInt(ctx.queryParam("day"));
        String gribFile = ctx.queryParam("grib_file");

        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND month = ? AND day = ? AND grib_file = ?";
            
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setDouble(1, latitude);
                statement.setDouble(2, longitude);
                statement.setInt(3, month);
                statement.setInt(4, day);
                statement.setString(5, gribFile);

                ResultSet resultSet = statement.executeQuery();
                
                if (resultSet.next()) {
                    double maxTemperature = resultSet.getDouble(1);
                    ctx.result(String.valueOf(maxTemperature));
                } else {
                    ctx.status(404).result("No temperature data found.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            ctx.status(500).result("An error occurred while processing your request.");
        }
    }
}
