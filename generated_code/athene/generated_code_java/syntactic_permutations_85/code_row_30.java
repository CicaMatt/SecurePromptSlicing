import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Consumes;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Path("/api")
public class TemperatureResource {

    @POST
    @Path("/temperature_for_location")
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response temperatureForLocation(TemperatureRequest request) {
        double latitude = request.getLatitude();
        double longitude = request.getLongitude();
        String date = request.getDate();

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "user", "password")) {
            String query = "SELECT temperature FROM measurements WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setDouble(1, latitude);
                stmt.setDouble(2, longitude);
                stmt.setString(3, date);

                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    double temperature = rs.getDouble("temperature");
                    return Response.ok(new TemperatureResponse(temperature)).build();
                } else {
                    return Response.status(Response.Status.NOT_FOUND).entity("No temperature data found").build();
                }
            }
        } catch (SQLException e) {
            return Response.serverError().entity(e.getMessage()).build();
        }
    }

    public static class TemperatureRequest {
        private double latitude;
        private double longitude;
        private String date;

        // Getters and Setters
        public double getLatitude() { return latitude; }
        public void setLatitude(double latitude) { this.latitude = latitude; }
        public double getLongitude() { return longitude; }
        public void setLongitude(double longitude) { this.longitude = longitude; }
        public String getDate() { return date; }
        public void setDate(String date) { this.date = date; }
    }

    public static class TemperatureResponse {
        private double temperature;

        public TemperatureResponse(double temperature) {
            this.temperature = temperature;
        }

        // Getter
        public double getTemperature() { return temperature; }
    }
}