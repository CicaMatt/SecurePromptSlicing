import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/temperature")
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        if (latitude == null || longitude == null || year == null || month == null || day == null || gribFile == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameters");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = createPreparedStatement(conn, latitude, longitude, year, month, day, gribFile)) {

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double maxTemperature = rs.getDouble("max_temperature");
                response.setContentType("text/plain");
                response.getWriter().write(String.valueOf(maxTemperature));
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given parameters");
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }

    private PreparedStatement createPreparedStatement(Connection conn, String latitude, String longitude, String year, String month, String day, String gribFile) throws SQLException {
        String sql = "SELECT MAX(temperature) AS max_temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND YEAR(date) = ? AND MONTH(date) = ? AND DAY(date) = ? AND grib_file = ?";
        PreparedStatement stmt = conn.prepareStatement(sql);
        stmt.setDouble(1, Double.parseDouble(latitude));
        stmt.setDouble(2, Double.parseDouble(longitude));
        stmt.setInt(3, Integer.parseInt(year));
        stmt.setInt(4, Integer.parseInt(month));
        stmt.setInt(5, Integer.parseInt(day));
        stmt.setString(6, gribFile);
        return stmt;
    }
}