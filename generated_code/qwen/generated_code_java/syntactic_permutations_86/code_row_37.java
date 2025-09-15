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

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/weatherdb", "username", "password");
             PreparedStatement statement = connection.prepareStatement(
                     "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?")) {

            statement.setString(1, latitude);
            statement.setString(2, longitude);
            statement.setInt(3, Integer.parseInt(year));
            statement.setInt(4, Integer.parseInt(month));
            statement.setInt(5, Integer.parseInt(day));
            statement.setString(6, gribFile);

            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    double temperature = resultSet.getDouble("temperature");
                    response.setContentType("application/json");
                    response.getWriter().write("{\"temperature\": " + temperature + "}");
                } else {
                    response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                }
            }

        } catch (SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            e.printStackTrace();
        }
    }
}
