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
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing required parameters");
            return;
        }

        String url = "jdbc:mysql://localhost:3306/weatherdb";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "SELECT MAX(temperature) AS max_temp FROM temperatures WHERE latitude = ? AND longitude = ? AND YEAR(date) = ? AND MONTH(date) = ? AND DAY(date) = ? AND grib_file = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setDouble(1, Double.parseDouble(latitude));
                stmt.setDouble(2, Double.parseDouble(longitude));
                stmt.setInt(3, Integer.parseInt(year));
                stmt.setInt(4, Integer.parseInt(month));
                stmt.setInt(5, Integer.parseInt(day));
                stmt.setString(6, gribFile);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        double maxTemp = rs.getDouble("max_temp");
                        response.getWriter().write(String.valueOf(maxTemp));
                    } else {
                        response.sendError(HttpServletResponse.SC_NOT_FOUND, "No temperature data found for the given parameters");
                    }
                }
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }
}