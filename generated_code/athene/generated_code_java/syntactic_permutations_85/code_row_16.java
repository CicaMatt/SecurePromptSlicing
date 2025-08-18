import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");

        double temperature = getTemperatureFromDatabase(latitude, longitude);

        response.setContentType("application/json");
        response.getWriter().write("{\"temperature\": " + temperature + "}");
    }

    private double getTemperatureFromDatabase(String latitude, String longitude) {
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "user", "password")) {
            String query = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, latitude);
                preparedStatement.setString(2, longitude);
                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next()) {
                        return resultSet.getDouble("temperature");
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -999.0; // Return a default value or handle the case where no temperature is found
    }
}