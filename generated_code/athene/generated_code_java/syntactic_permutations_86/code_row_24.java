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
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherDB";
    private static final String USER = "root";
    private static final String PASS = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String latitude = request.getParameter("latitude");
        int year = Integer.parseInt(request.getParameter("year"));
        int month = Integer.parseInt(request.getParameter("month"));
        int day = Integer.parseInt(request.getParameter("day"));
        String grib_file = request.getParameter("grib_file");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT MAX(temperature) FROM weather_data WHERE latitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, latitude);
            stmt.setInt(2, year);
            stmt.setInt(3, month);
            stmt.setInt(4, day);
            stmt.setString(5, grib_file);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double maxTemperature = rs.getDouble(1);
                response.getWriter().write("Max Temperature: " + maxTemperature);
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given parameters.");
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while processing your request.");
            e.printStackTrace();
        }
    }
}