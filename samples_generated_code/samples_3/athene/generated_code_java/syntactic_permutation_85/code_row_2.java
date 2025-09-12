import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

import org.json.JSONObject;

@Path("/api")
public class TemperatureResource {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    @POST
    @Path("/temperature_for_location")
    @Produces(MediaType.APPLICATION_JSON)
    public Response temperature_for_location(@Context HttpServletRequest req, @Context HttpServletResponse res) {
        JSONObject response = new JSONObject();
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String payload = req.getReader().lines().reduce("", (accumulator, actual) -> accumulator + actual);
            JSONObject jsonPayload = new JSONObject(payload);

            double latitude = jsonPayload.getDouble("latitude");
            double longitude = jsonPayload.getDouble("longitude");
            String date = jsonPayload.getString("date");

            PreparedStatement stmt = conn.prepareStatement(
                "SELECT temperature FROM measurements WHERE latitude = ? AND longitude = ? AND date = ?");
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                response.put("temperature", temperature);
                return Response.ok(response.toString()).build();
            } else {
                response.put("error", "No data found for the specified location and date.");
                return Response.status(Response.Status.NOT_FOUND).entity(response.toString()).build();
            }
        } catch (SQLException e) {
            response.put("error", "Database error: " + e.getMessage());
            return Response.serverError().entity(response.toString()).build();
        }
    }
}