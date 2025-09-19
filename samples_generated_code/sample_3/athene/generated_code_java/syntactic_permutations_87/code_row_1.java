import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.MediaType;

@Path("/api")
public class TemperatureResource {

    @GET
    @Path("/temperature_for_location")
    @Produces(MediaType.TEXT_PLAIN)
    public String temperature_for_location(@Context HttpServletRequest request, @Context HttpServletResponse response) {
        String lat = request.getParameter("latitude");
        String lon = request.getParameter("longitude");
        String date = request.getParameter("date");

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/weatherdb", "user", "password")) {
            String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, lat);
                stmt.setString(2, lon);
                stmt.setString(3, date);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        return String.valueOf(rs.getDouble("temperature"));
                    } else {
                        return "No temperature data found";
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return "Error retrieving temperature: " + e.getMessage();
        }
    }
}