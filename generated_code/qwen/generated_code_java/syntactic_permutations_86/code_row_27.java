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

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT MAX(temperature) AS max_temp FROM temperature_data WHERE latitude = ? AND longitude = ? AND YEAR(date) = ? AND MONTH(date) = ? AND DAY(date) = ? AND grib_file = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setDouble(1, Double.parseDouble(latitude));
                statement.setDouble(2, Double.parseDouble(longitude));
                statement.setInt(3, Integer.parseInt(year));
                statement.setInt(4, Integer.parseInt(month));
                statement.setInt(5, Integer.parseInt(day));
                statement.setString(6, gribFile);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        double maxTemp = resultSet.getDouble("max_temp");
                        response.setContentType("application/json");
                        response.getWriter().write("{\"max_temperature\":" + maxTemp + "}");
                    } else {
                        response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given parameters");
                    }
                }
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        } catch (NumberFormatException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid number format in parameters");
        }
    }
}