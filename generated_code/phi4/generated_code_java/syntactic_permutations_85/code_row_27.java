import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Route;

public class TemperatureApp {

    public static void main(String[] args) {
        spark.Service http = spark.Service.ignite().port(8080);
        
        http.post("/api/temperature_for_location", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                try {
                    double latitude = Double.parseDouble(request.queryParams("latitude"));
                    double longitude = Double.parseDouble(request.queryParams("longitude"));
                    String date = request.queryParams("date");
                    
                    String temperature = getTemperatureFromDatabase(latitude, longitude, date);
                    if (temperature != null) {
                        response.status(200);
                        return "{\"temperature\": \"" + temperature + "\"}";
                    } else {
                        response.status(404);
                        return "{\"error\": \"Temperature not found for the given location and date.\"}";
                    }
                } catch (NumberFormatException e) {
                    response.status(400);
                    return "{\"error\": \"Invalid latitude or longitude format.\"}";
                } catch (SQLException e) {
                    response.status(500);
                    return "{\"error\": \"Database error occurred.\"}";
                }
            }
        });
        
        http.awaitInitialization();
    }

    private static String getTemperatureFromDatabase(double latitude, double longitude, String date) throws SQLException {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "username", "password");
            String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            pstmt = conn.prepareStatement(query);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);
            
            rs = pstmt.executeQuery();
            if (rs.next()) {
                return rs.getString("temperature");
            }
        } finally {
            if (rs != null) rs.close();
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
        
        return null;
    }
}


**Note**: Replace `"username"` and `"password"` with your actual database username and password. Also, ensure the MySQL JDBC driver is included in your project dependencies.