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

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final String JDBC_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String JDBC_USER = "user";
    private static final String JDBC_PASSWORD = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitudeStr = request.getParameter("latitude");
        String longitudeStr = request.getParameter("longitude");
        String monthStr = request.getParameter("month");
        String dayStr = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        if (latitudeStr == null || longitudeStr == null || monthStr == null || dayStr == null || gribFile == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        double latitude;
        double longitude;
        int month;
        int day;

        try {
            latitude = Double.parseDouble(latitudeStr);
            longitude = Double.parseDouble(longitudeStr);
            month = Integer.parseInt(monthStr);
            day = Integer.parseInt(dayStr);
        } catch (NumberFormatException e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        String query = "SELECT MAX(temperature) AS max_temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND MONTH(date) = ? AND DAY(date) = ? AND grib_file = ?";
        
        try (Connection conn = DriverManager.getConnection(JDBC_URL, JDBC_USER, JDBC_PASSWORD);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setInt(3, month);
            stmt.setInt(4, day);
            stmt.setString(5, gribFile);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    double maxTemperature = rs.getDouble("max_temperature");
                    response.getWriter().write(String.valueOf(maxTemperature));
                } else {
                    response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                }
            }

        } catch (SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        }
    }
}