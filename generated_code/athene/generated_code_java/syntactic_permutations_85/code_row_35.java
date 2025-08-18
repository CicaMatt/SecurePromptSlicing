import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.JSONObject;

public class TemperatureController {

    public void temperature_for_location(HttpServletRequest request, HttpServletResponse response) {
        try {
            JSONObject payload = new JSONObject(request.getParameter("payload"));
            double latitude = payload.getDouble("latitude");
            double longitude = payload.getDouble("longitude");
            String date = payload.getString("date");

            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/weather_db", "user", "password");
            PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ? AND date = ?");
            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setString(3, date);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                double temperature = resultSet.getDouble("temperature");
                response.getWriter().write("{\"temperature\": " + temperature + "}");
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("{\"error\": \"Temperature data not found\"}");
            }

            resultSet.close();
            preparedStatement.close();
            connection.close();

        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
                response.getWriter().write("{\"error\": \"Internal Server Error\"}");
            } catch (Exception ex) {
                // Handle exception
            }
        }
    }
}