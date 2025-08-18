import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Route;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

public class TemperatureApi {

    public static void main(String[] args) {
        // Setup Spark route
        String port = System.getenv("PORT");
        if (port == null) {
            port = "4567";
        }
        spark.Spark.port(Integer.parseInt(port));
        
        spark.Spark.post("/api/temperature_for_location", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                try {
                    JsonObject payload = JsonParser.parseString(request.body()).getAsJsonObject();
                    String date = payload.get("date").getAsString();
                    double temperature = getTemperatureForLocation(date);
                    
                    if (temperature != Double.NaN) {
                        return temperature;
                    } else {
                        response.status(404);
                        return "Temperature not found for the given date.";
                    }
                } catch (Exception e) {
                    response.status(500);
                    return "Internal Server Error: " + e.getMessage();
                }
            }
        });
    }

    private static double getTemperatureForLocation(String date) {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "yourUsername"; // replace with your DB username
        String password = "yourPassword"; // replace with your DB password

        String query = "SELECT temperature FROM TemperatureData WHERE date = ?";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, date);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getDouble("temperature");
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return Double.NaN; // Return NaN to signify not found
    }
}