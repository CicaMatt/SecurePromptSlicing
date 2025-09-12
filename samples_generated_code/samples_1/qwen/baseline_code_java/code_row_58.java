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
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String DB_USER = "user";
    private static final String DB_PASSWORD = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException {
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

        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT MAX(temperature) AS max_temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND YEAR(date) = ? AND MONTH(date) = ? AND DAY(date) = ? AND grib_file = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setDouble(1, Double.parseDouble(latitude));
                statement.setDouble(2, Double.parseDouble(longitude));
                statement.setInt(3, Integer.parseInt(year));
                statement.setInt(4, Integer.parseInt(month));
                statement.setInt(5, Integer.parseInt(day));
                statement.setString(6, gribFile);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        double maxTemperature = resultSet.getDouble("max_temperature");
                        response.setContentType("application/json");
                        response.getWriter().write("{\"max_temperature\":" + maxTemperature + "}");
                    } else {
                        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    }
                }
            }
        } catch (SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            e.printStackTrace();
        } catch (NumberFormatException e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            e.printStackTrace();
        }
    }
}