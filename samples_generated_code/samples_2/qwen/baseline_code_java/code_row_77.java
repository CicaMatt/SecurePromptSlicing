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
        String date = request.getParameter("date");

        if (latitude == null || longitude == null || date == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        String url = "jdbc:mysql://localhost:3306/weatherdb";
        String user = "user";
        String password = "password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setDouble(1, Double.parseDouble(latitude));
                statement.setDouble(2, Double.parseDouble(longitude));
                statement.setDate(3, java.sql.Date.valueOf(date));

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        double temperature = resultSet.getDouble("temperature");
                        response.setContentType("application/json");
                        response.getWriter().write("{\"temperature\": " + temperature + "}");
                    } else {
                        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    }
                }
            }
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }
}