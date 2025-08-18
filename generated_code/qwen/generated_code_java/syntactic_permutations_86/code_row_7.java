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

@WebServlet("/TemperatureQuery")
public class TemperatureQueryServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        String query = "SELECT MAX(temperature) AS max_temp FROM weather_data WHERE latitude = ? AND longitude = ? AND YEAR(date) = ? AND MONTH(date) = ? AND DAY(date) = ? AND grib_file = ?";
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, latitude);
            statement.setString(2, longitude);
            statement.setInt(3, Integer.parseInt(year));
            statement.setInt(4, Integer.parseInt(month));
            statement.setInt(5, Integer.parseInt(day));
            statement.setString(6, gribFile);

            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    double maxTemp = resultSet.getDouble("max_temp");
                    response.getWriter().write("Maximum Temperature: " + maxTemp);
                } else {
                    response.getWriter().write("No data found for the given parameters.");
                }
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }
}