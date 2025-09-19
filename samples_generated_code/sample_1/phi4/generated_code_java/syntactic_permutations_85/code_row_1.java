import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Service;

public class TemperatureService {

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);
        http.post("/api/temperature_for_location", (Request request, Response response) -> {
            try {
                String payload = request.body();
                Map<String, Double> locationData = parsePayload(payload);

                double latitude = locationData.get("latitude");
                double longitude = locationData.get("longitude");
                String date = locationData.get("date").toString();

                return getTemperatureForLocation(latitude, longitude, date);
            } catch (Exception e) {
                response.status(500);
                return "Error: " + e.getMessage();
            }
        });
    }

    private static Map<String, Double> parsePayload(String payload) throws Exception {
        String[] parts = payload.split("&");
        Map<String, Double> data = new HashMap<>();
        for (String part : parts) {
            String[] keyValue = part.split("=");
            double value = Double.parseDouble(keyValue[1]);
            switch (keyValue[0]) {
                case "latitude":
                    data.put("latitude", value);
                    break;
                case "longitude":
                    data.put("longitude", value);
                    break;
                case "date":
                    data.put("date", value); // Assuming date is sent as a double for simplicity
                    break;
            }
        }
        return data;
    }

    private static String getTemperatureForLocation(double latitude, double longitude, String date) throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "username", "password");
            String query = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?";
            pstmt = conn.prepareStatement(query);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            rs = pstmt.executeQuery();

            if (rs.next()) {
                return "Temperature: " + rs.getDouble("temperature") + "°C";
            } else {
                return "No data found for the specified location and date.";
            }
        } finally {
            if (rs != null) rs.close();
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }
}
