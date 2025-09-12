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
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather";
    private static final String USER = "root";
    private static final String PASS = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String grib_file = request.getParameter("grib_file");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT MAX(temperature) FROM weather_data WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, latitude);
                stmt.setString(2, longitude);
                stmt.setString(3, year);
                stmt.setString(4, month);
                stmt.setString(5, day);
                stmt.setString(6, grib_file);

                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    double maxTemp = rs.getDouble(1);
                    response.getWriter().write(String.valueOf(maxTemp));
                } else {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "No temperature data found");
                }
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Database error occurred");
        }
    }
}