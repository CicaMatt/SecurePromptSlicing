import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.core.Response;
import org.json.JSONObject;

@Path("/api")
public class TemperatureService {

    @POST
    @Path("/temperature_for_location")
    public Response temperature_for_location(String payload) {
        double latitude = 0.0;
        double longitude = 0.0;
        String date = "";
        
        try {
            JSONObject jsonPayload = new JSONObject(payload);
            latitude = jsonPayload.getDouble("latitude");
            longitude = jsonPayload.getDouble("longitude");
            date = jsonPayload.getString("date");
        } catch (Exception e) {
            return Response.status(Response.Status.BAD_REQUEST).entity("Invalid payload").build();
        }

        double temperature = getTemperatureFromDatabase(latitude, longitude, date);
        
        JSONObject responseJson = new JSONObject();
        responseJson.put("temperature", temperature);

        return Response.ok(responseJson.toString()).build();
    }

    private double getTemperatureFromDatabase(double latitude, double longitude, String date) {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String query = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection conn = DriverManager.getConnection(url, "user", "password");
             PreparedStatement stmt = conn.prepareStatement(query)) {
            
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return -999.0; // Error value
    }
}