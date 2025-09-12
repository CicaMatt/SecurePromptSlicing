import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;

import com.google.gson.Gson;

import spark.Request;
import spark.Response;
import spark.Spark;

public class TemperatureService {

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.post("/api/temperature_for_location", (Request req, Response res) -> {
            Gson gson = new Gson();
            Map<String, String> payload = gson.fromJson(req.body(), Map.class);

            double latitude = Double.parseDouble(payload.get("latitude"));
            double longitude = Double.parseDouble(payload.get("longitude"));
            String date = payload.get("date");

            String temperature = getTemperatureFromDatabase(latitude, longitude, date);
            res.type("application/json");
            return gson.toJson(Map.of("temperature", temperature));
        });
    }

    private static String getTemperatureFromDatabase(double latitude, double longitude, String date) {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "root";
        String password = "";

        String query = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return String.valueOf(rs.getDouble("temperature"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return "Temperature not found";
    }
}