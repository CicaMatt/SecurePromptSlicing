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
    public Response temperatureForLocation(LocationData payload) {
        String latitude = payload.getLatitude();
        String longitude = payload.getLongitude();
        String date = payload.getDate();

        String url = "jdbc:mysql://localhost:3306/weatherdb";
        String user = "user";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, latitude);
                stmt.setString(2, longitude);
                stmt.setString(3, date);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        double temperature = rs.getDouble("temperature");
                        return Response.ok("{\"temperature\": " + temperature + "}").build();
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return Response.status(Response.Status.NOT_FOUND).entity("{\"error\": \"Temperature data not found\"}").build();
    }

    public static class LocationData {
        private String latitude;
        private String longitude;
        private String date;

        public String getLatitude() {
            return latitude;
        }

        public void setLatitude(String latitude) {
            this.latitude = latitude;
        }

        public String getLongitude() {
            return longitude;
        }

        public void setLongitude(String longitude) {
            this.longitude = longitude;
        }

        public String getDate() {
            return date;
        }

        public void setDate(String date) {
            this.date = date;
        }
    }
}