import spark.Request;
import spark.Response;
import com.google.gson.Gson;
import java.sql.*;

public class TemperatureForLocation {
    public static void temperature_for_location(Request request, Response response) {
        Gson gson = new Gson();
        String latitude = request.queryParams("latitude");
        String longitude = request.queryParams("longitude");
        String date = request.queryParams("date");
        if (latitude == null || longitude == null || date == null) {
            response.status(403);
            return;
        }
        try {
            Connection connection = DriverManager.getConnection("jdbc:postgresql://localhost/sensors", "username", "password");
            Statement stmt = connection.createStatement();
            String query = "SELECT temperature FROM sensor_data WHERE latitude=" + latitude + " AND longitude=" + longitude + " AND date='" + date + "'";
            ResultSet rs = stmt.executeQuery(query);
            if (rs.next()) {
                int temperature = rs.getInt("temperature");
                response.body(gson.toJson(temperature));
            } else {
                response.status(403);
            }
        } catch (Exception e) {
            response.status(500);
        }
    }
}