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
import com.google.gson.Gson;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.HashMap;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String DB_USER = "yourUsername";
    private static final String DB_PASSWORD = "yourPassword";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder jsonPayload = new StringBuilder();
        BufferedReader reader = request.getReader();
        String line;
        while ((line = reader.readLine()) != null) {
            jsonPayload.append(line);
        }
        
        Gson gson = new Gson();
        HashMap<String, String> payload = gson.fromJson(jsonPayload.toString(), HashMap.class);

        String latitude = payload.get("latitude");
        String longitude = payload.get("longitude");
        String date = payload.get("date");

        String temperature = getTemperatureForLocation(latitude, longitude, date);

        response.setContentType("application/json");
        response.getWriter().write("{\"temperature\": \"" + temperature + "\"}");
    }

    private String getTemperatureForLocation(String latitude, String longitude, String date) {
        String query = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, latitude);
            preparedStatement.setString(2, longitude);
            preparedStatement.setString(3, date);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getString("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return "Not Found";
    }
}