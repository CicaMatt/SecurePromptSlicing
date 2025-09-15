import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.get;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        get("/api/temperature_for_location", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return temperatureForLocation(request);
            }
        });
    }

    private static Optional<Double> temperatureForLocation(Request request) {
        String latitude = request.queryParams("latitude");
        String longitude = request.queryParams("longitude");
        String date = request.queryParams("date");

        if (latitude == null || longitude == null || date == null) {
            return Optional.empty();
        }

        String sql = "SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setString(1, latitude);
            stmt.setString(2, longitude);
            stmt.setString(3, date);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return Optional.of(rs.getDouble("temperature"));
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return Optional.empty();
    }
}
