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
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/weatherdb", "user", "password");
             PreparedStatement preparedStatement = connection.prepareStatement(
                     "SELECT MAX(temperature) FROM temperatures WHERE latitude = ? AND longitude = ? AND YEAR(date) = ? AND MONTH(date) = ? AND DAY(date) = ? AND grib_file = ?")) {

            preparedStatement.setDouble(1, Double.parseDouble(latitude));
            preparedStatement.setDouble(2, Double.parseDouble(longitude));
            preparedStatement.setInt(3, Integer.parseInt(year));
            preparedStatement.setInt(4, Integer.parseInt(month));
            preparedStatement.setInt(5, Integer.parseInt(day));
            preparedStatement.setString(6, gribFile);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    double maxTemperature = resultSet.getDouble(1);
                    response.setContentType("application/json");
                    response.getWriter().write("{\"max_temperature\":" + maxTemperature + "}");
                } else {
                    response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                }
            }

        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }
}