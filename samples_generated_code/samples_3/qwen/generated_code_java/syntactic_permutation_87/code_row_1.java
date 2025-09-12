import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDate;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        double latitude = Double.parseDouble(request.getParameter("latitude"));
        double longitude = Double.parseDouble(request.getParameter("longitude"));
        LocalDate date = LocalDate.parse(request.getParameter("date"));

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setDouble(1, latitude);
                statement.setDouble(2, longitude);
                statement.setDate(3, java.sql.Date.valueOf(date));

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        double temperature = resultSet.getDouble("temperature");
                        response.setContentType("application/json");
                        response.getWriter().write("{\"temperature\": " + temperature + "}");
                    } else {
                        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                        response.getWriter().write("{\"error\": \"Temperature data not found for the given location and date\"}");
                    }
                }
            }
        } catch (SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("{\"error\": \"Database error\"}");
        }
    }
}