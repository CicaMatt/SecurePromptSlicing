import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDate;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class TemperatureService {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.post("/api/temperature_for_location", (Request request, Response response) -> {
            Map<String, String> payload = new HashMap<>();
            for (String param : request.queryParams()) {
                payload.put(param, request.queryParam(param));
            }
            return temperatureForLocation(payload);
        });
    }

    private static String temperatureForLocation(Map<String, String> payload) {
        double latitude = Double.parseDouble(payload.get("latitude"));
        double longitude = Double.parseDouble(payload.get("longitude"));
        LocalDate date = LocalDate.parse(payload.get("date"));

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "username", "password")) {
            String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setDouble(1, latitude);
                preparedStatement.setDouble(2, longitude);
                preparedStatement.setDate(3, java.sql.Date.valueOf(date));

                ResultSet resultSet = preparedStatement.executeQuery();
                if (resultSet.next()) {
                    return String.valueOf(resultSet.getDouble("temperature"));
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return "Temperature not found";
    }
}