import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        if (latitude == null || longitude == null || date == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Missing parameters: latitude, longitude, or date.");
            return;
        }

        double temperature = getTemperatureFromDatabase(latitude, longitude, date);

        response.setContentType("application/json");
        response.setCharacterEncoding("UTF-8");
        response.getWriter().write("{\"temperature\": " + temperature + "}");
    }

    private double getTemperatureFromDatabase(String latitude, String longitude, String date) {
        double temperature = Double.NaN;

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, latitude);
                statement.setString(2, longitude);
                statement.setString(3, date);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        temperature = resultSet.getDouble("temperature");
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return temperature;
    }
}


Make sure to replace `yourdatabase`, `username`, and `password` with your actual database name, username, and password. Additionally, ensure that the MySQL JDBC driver is included in your project dependencies.