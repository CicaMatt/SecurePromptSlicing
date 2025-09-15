import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.Response;

@Path("/api")
public class TemperatureApi {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "yourUsername"; // replace with your database username
    private static final String PASS = "yourPassword"; // replace with your database password

    @GET
    @Path("/temperature_for_location")
    public Response temperatureForLocation(@QueryParam("latitude") double latitude,
                                           @QueryParam("longitude") double longitude,
                                           @QueryParam("date") String date) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setDouble(1, latitude);
                pstmt.setDouble(2, longitude);
                pstmt.setString(3, date);

                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next()) {
                        double temperature = rs.getDouble("temperature");
                        return Response.ok(String.valueOf(temperature)).build();
                    } else {
                        return Response.status(Response.Status.NOT_FOUND).entity("Temperature not found").build();
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            return Response.status(Response.Status.INTERNAL_SERVER_ERROR).entity("Error connecting to database").build();
        }
    }

    public static void main(String[] args) throws Exception {
        // Start the server or test the API as needed
    }
}
