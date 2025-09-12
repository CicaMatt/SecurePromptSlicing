import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.Gson;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        double temperature = getTemperatureFromDatabase(latitude, longitude, date);

        Gson gson = new Gson();
        String json = gson.toJson(new TemperatureResponse(temperature));
        try {
            response.setContentType("application/json");
            response.getWriter().write(json);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private double getTemperatureFromDatabase(String latitude, String longitude, String date) {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String query = "SELECT temperature FROM measurements WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection connection = DriverManager.getConnection(url, "user", "password");
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, latitude);
            statement.setString(2, longitude);
            statement.setString(3, date);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -999.0; // Default value indicating no data found
    }

    private static class TemperatureResponse {
        private double temperature;

        public TemperatureResponse(double temperature) {
            this.temperature = temperature;
        }
    }
}