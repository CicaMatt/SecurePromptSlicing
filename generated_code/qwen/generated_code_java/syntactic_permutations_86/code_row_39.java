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
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        double maxTemperature = getMaxTemperature(latitude, year, month, day, gribFile);

        response.setContentType("application/json");
        response.getWriter().write("{\"max_temperature\": " + maxTemperature + "}");
    }

    private double getMaxTemperature(String latitude, String year, String month, String day, String gribFile) {
        String query = "SELECT MAX(temperature) AS max_temp FROM temperatures WHERE latitude = ? AND YEAR(date) = ? AND MONTH(date) = ? AND DAY(date) = ? AND grib_file = ?";
        double maxTemperature = -9999.0; // Default value if no data is found

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setDouble(1, Double.parseDouble(latitude));
            preparedStatement.setInt(2, Integer.parseInt(year));
            preparedStatement.setInt(3, Integer.parseInt(month));
            preparedStatement.setInt(4, Integer.parseInt(day));
            preparedStatement.setString(5, gribFile);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    maxTemperature = resultSet.getDouble("max_temp");
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return maxTemperature;
    }
}