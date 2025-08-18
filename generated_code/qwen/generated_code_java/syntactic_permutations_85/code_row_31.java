import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.ws.rs.Consumes;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import com.google.gson.JsonObject;

@Path("/api")
public class TemperatureResource {

    @POST
    @Path("/temperature_for_location")
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public String temperature_for_location(String payload) {
        JsonObject jsonObject = new JsonObject();
        double latitude = 0.0;
        double longitude = 0.0;
        String date = "";

        try {
            JsonObject requestJson = com.google.gson.JsonParser.parseString(payload).getAsJsonObject();
            latitude = requestJson.get("latitude").getAsDouble();
            longitude = requestJson.get("longitude").getAsDouble();
            date = requestJson.get("date").getAsString();
        } catch (Exception e) {
            jsonObject.addProperty("error", "Invalid payload");
            return jsonObject.toString();
        }

        String temperature = getTemperatureFromDatabase(latitude, longitude, date);

        if (temperature != null) {
            jsonObject.addProperty("temperature", temperature);
        } else {
            jsonObject.addProperty("error", "Temperature not found");
        }

        return jsonObject.toString();
    }

    private String getTemperatureFromDatabase(double latitude, double longitude, String date) {
        String url = "jdbc:mysql://localhost:3306/weatherdb";
        String user = "user";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT temperature FROM weather WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getString("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return null;
    }
}