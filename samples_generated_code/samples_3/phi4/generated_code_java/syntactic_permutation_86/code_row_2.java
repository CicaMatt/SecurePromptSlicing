import io.javalin.Javalin;
import io.javalin.http.Context;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureApp {

    private static final Logger logger = LoggerFactory.getLogger(TemperatureApp.class);

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType("application/json"))
                .start(7000);

        app.post("/api/temperature_for_location", ctx -> handleTemperatureRequest(ctx));
    }

    private static void handleTemperatureRequest(Context ctx) {
        try {
            double latitude = Double.parseDouble(ctx.queryParam("latitude"));
            double longitude = Double.parseDouble(ctx.queryParam("longitude"));
            int year = Integer.parseInt(ctx.queryParam("year"));
            int month = Integer.parseInt(ctx.queryParam("month"));
            int day = Integer.parseInt(ctx.queryParam("day"));
            String gribFile = ctx.queryParam("grib_file");

            Connection connection = connectToDatabase();
            double maxTemperature = getMaxTemperature(connection, latitude, longitude, year, month, day, gribFile);

            ctx.json(Map.of("max_temperature", maxTemperature));
        } catch (Exception e) {
            logger.error("Error processing request: ", e);
            ctx.status(500).result("Internal Server Error");
        }
    }

    private static Connection connectToDatabase() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        return DriverManager.getConnection(url, user, password);
    }

    private static double getMaxTemperature(Connection connection, double latitude, double longitude,
                                            int year, int month, int day, String gribFile) throws SQLException {
        String query = "SELECT MAX(temperature) FROM temperature_data WHERE "
                + "latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
        
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setInt(3, year);
            statement.setInt(4, month);
            statement.setInt(5, day);
            statement.setString(6, gribFile);

            ResultSet resultSet = statement.executeQuery();
            
            if (resultSet.next()) {
                return resultSet.getDouble(1);
            } else {
                throw new SQLException("No temperature data found for the given parameters.");
            }
        }
    }
}
