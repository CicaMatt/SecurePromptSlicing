import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String latitude = req.getParameter("latitude");
        String longitude = req.getParameter("longitude");
        String year = req.getParameter("year");
        String month = req.getParameter("month");
        String day = req.getParameter("day");
        String gribFile = req.getParameter("grib_file");

        if (latitude == null || longitude == null || year == null || month == null || day == null || gribFile == null) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "All parameters are required: latitude, longitude, year, month, day, grib_file");
            return;
        }

        String sql = "SELECT MAX(temperature) AS max_temp FROM weather_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
        
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/weatherdb", "user", "password");
             PreparedStatement ps = conn.prepareStatement(sql)) {
            
            ps.setString(1, latitude);
            ps.setString(2, longitude);
            ps.setString(3, year);
            ps.setString(4, month);
            ps.setString(5, day);
            ps.setString(6, gribFile);

            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    double maxTemp = rs.getDouble("max_temp");
                    resp.getWriter().write(String.format("%.2f", maxTemp));
                } else {
                    resp.sendError(HttpServletResponse.SC_NOT_FOUND, "No temperature data found for the given parameters.");
                }
            }
        } catch (Exception e) {
            resp.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while processing your request: " + e.getMessage());
        }
    }
}