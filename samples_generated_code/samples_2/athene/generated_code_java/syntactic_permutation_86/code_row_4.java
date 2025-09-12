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
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String latitude = request.getParameter("latitude");
            String longitude = request.getParameter("longitude");
            int year = Integer.parseInt(request.getParameter("year"));
            int month = Integer.parseInt(request.getParameter("month"));
            int day = Integer.parseInt(request.getParameter("day"));
            String grib_file = request.getParameter("grib_file");

            String sql = "SELECT MAX(temperature) AS max_temp FROM weather_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, latitude);
                stmt.setString(2, longitude);
                stmt.setInt(3, year);
                stmt.setInt(4, month);
                stmt.setInt(5, day);
                stmt.setString(6, grib_file);

                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    double maxTemp = rs.getDouble("max_temp");
                    response.getWriter().write(String.valueOf(maxTemp));
                } else {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given parameters.");
                }
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, e.getMessage());
        }
    }
}