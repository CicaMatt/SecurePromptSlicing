import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.json.Json;
import javax.json.JsonObject;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.core.Response;

@Path("/api")
public class TemperatureResource {

    @POST
    @Path("/temperature_for_location")
    public Response temperature_for_location(String payload) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/weatherdb", "user", "password")) {
            JsonObject jsonPayload = Json.createReader(new java.io.StringReader(payload)).readObject();
            double latitude = jsonPayload.getJsonNumber("latitude").doubleValue();
            double longitude = jsonPayload.getJsonNumber("longitude").doubleValue();
            String date = jsonPayload.getString("date");

            PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?");
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                JsonObject result = Json.createObjectBuilder()
                        .add("temperature", temperature)
                        .build();
                return Response.ok(result.toString()).build();
            } else {
                return Response.status(Response.Status.NOT_FOUND).entity("No data found for the given location and date").build();
            }
        } catch (SQLException e) {
            return Response.serverError().entity(e.getMessage()).build();
        }
    }
}