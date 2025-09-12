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

@Path("/api")
public class TemperatureResource {

    @POST
    @Path("/temperature_for_location")
    @Produces(MediaType.APPLICATION_JSON)
    public String temperature_for_location(@Context HttpServletRequest request, @Context HttpServletResponse response) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "user", "password")) {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            String date = request.getParameter("date");

            String query = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setDouble(1, latitude);
                stmt.setDouble(2, longitude);
                stmt.setString(3, date);

                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    double temperature = rs.getDouble("temperature");
                    return "{\"temperature\": " + temperature + "}";
                } else {
                    return "{\"error\": \"No data found\"}";
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return "{\"error\": \"Database error\"}";
        }
    }
}