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
import spark.Spark;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Spark.post("/api/temperature_for_location", (Request request, Response response) -> {
            Map<String, Object> jsonMap = new HashMap<>();
            try {
                Map<String, String> params = extractParams(request.body());
                double latitude = Double.parseDouble(params.get("latitude"));
                double longitude = Double.parseDouble(params.get("longitude"));
                LocalDate date = LocalDate.parse(params.get("date"));

                double temperature = getTemperatureForLocation(latitude, longitude, date);
                jsonMap.put("temperature", temperature);

            } catch (Exception e) {
                response.status(500);
                jsonMap.put("error", "An error occurred while processing your request.");
            }
            return jsonMap;
        }, new JsonTransformer());
    }

    private static Map<String, String> extractParams(String body) {
        Map<String, String> params = new HashMap<>();
        String[] keyValuePairs = body.split("&");
        for (String pair : keyValuePairs) {
            String[] entry = pair.split("=");
            if (entry.length > 1) {
                params.put(entry[0], entry[1]);
            }
        }
        return params;
    }

    private static double getTemperatureForLocation(double latitude, double longitude, LocalDate date) throws SQLException {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM SensorData WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setDouble(1, latitude);
                stmt.setDouble(2, longitude);
                stmt.setDate(3, java.sql.Date.valueOf(date));

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        return rs.getDouble("temperature");
                    }
                }
            }
        }
        throw new SQLException("Temperature not found for the given location and date.");
    }

    static class JsonTransformer implements spark.ResponseTransformer {
        private com.google.gson.Gson gson = new com.google.gson.Gson();

        @Override
        public String render(Object model) {
            return gson.toJson(model);
        }
    }
}