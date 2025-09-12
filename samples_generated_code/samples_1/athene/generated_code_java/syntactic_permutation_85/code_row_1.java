import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import org.json.JSONObject;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "user", "password")) {
            String query = "SELECT temperature FROM measurements WHERE latitude = ? AND longitude = ? AND DATE(date_time) = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, latitude);
                statement.setString(2, longitude);
                statement.setString(3, date);

                ResultSet resultSet = statement.executeQuery();
                if (resultSet.next()) {
                    double temperature = resultSet.getDouble("temperature");
                    JSONObject json = new JSONObject().put("temperature", temperature);
                    response.getWriter().write(json.toString());
                } else {
                    response.setStatus(HttpServletResponse.SC_NO_CONTENT);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Database error");
        }
    }
}