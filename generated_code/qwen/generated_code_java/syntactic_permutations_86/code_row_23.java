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
    private static final long serialVersionUID = 1L;
    
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

        double lat = Double.parseDouble(latitude);
        double lon = Double.parseDouble(longitude);
        int yr = Integer.parseInt(year);
        int mnth = Integer.parseInt(month);
        int dy = Integer.parseInt(day);

        String url = "jdbc:mysql://localhost:3306/weatherdb";
        String user = "user";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT MAX(temperature) as max_temp FROM temperature_data WHERE latitude = ? AND longitude = ? AND YEAR(date) = ? AND MONTH(date) = ? AND DAY(date) = ? AND grib_file = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setDouble(1, lat);
                stmt.setDouble(2, lon);
                stmt.setInt(3, yr);
                stmt.setInt(4, mnth);
                stmt.setInt(5, dy);
                stmt.setString(6, gribFile);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        double maxTemp = rs.getDouble("max_temp");
                        response.getWriter().write(String.valueOf(maxTemp));
                    } else {
                        response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for given parameters");
                    }
                }
            }
        } catch (SQLException e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Database error: " + e.getMessage());
        }
    }
}