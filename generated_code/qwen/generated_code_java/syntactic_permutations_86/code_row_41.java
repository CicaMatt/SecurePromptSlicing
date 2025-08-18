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
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        if (latitude == null || longitude == null || year == null || day == null || gribFile == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameters");
            return;
        }

        String url = "jdbc:mysql://localhost:3306/weatherdb";
        String user = "user";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "SELECT MAX(temperature) as max_temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND YEAR(date) = ? AND DAYOFYEAR(date) = ? AND grib_file = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setDouble(1, Double.parseDouble(latitude));
                pstmt.setDouble(2, Double.parseDouble(longitude));
                pstmt.setInt(3, Integer.parseInt(year));
                pstmt.setInt(4, Integer.parseInt(day));
                pstmt.setString(5, gribFile);

                ResultSet rs = pstmt.executeQuery();
                if (rs.next()) {
                    double maxTemperature = rs.getDouble("max_temperature");
                    response.setContentType("application/json");
                    response.getWriter().write("{\"max_temperature\": " + maxTemperature + "}");
                } else {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given parameters");
                }
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }
}