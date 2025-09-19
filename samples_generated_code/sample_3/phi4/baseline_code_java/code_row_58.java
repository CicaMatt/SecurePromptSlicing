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
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameters.");
            return;
        }

        try (Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password")) {
            
            String query = "SELECT MAX(temperature) AS max_temperature "
                         + "FROM temperature_data "
                         + "WHERE latitude = ? AND longitude = ? "
                         + "AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                         
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, latitude);
                stmt.setString(2, longitude);
                stmt.setInt(3, Integer.parseInt(year));
                stmt.setInt(4, Integer.parseInt(month));
                stmt.setInt(5, Integer.parseInt(day));
                stmt.setString(6, gribFile);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        double maxTemperature = rs.getDouble("max_temperature");
                        response.getWriter().write(String.valueOf(maxTemperature));
                    } else {
                        response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given parameters.");
                    }
                }
            }
        } catch (SQLException e) {
            throw new ServletException("Database connection problem.", e);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }

    public static void main(String[] args) {
        // This method is just for standalone execution and testing.
        // It's not used in a servlet container environment like Tomcat or Jetty.
    }
}
