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

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Gson gson = new Gson();
        RequestPayload payload = gson.fromJson(request.getReader(), RequestPayload.class);

        double latitude = payload.getLatitude();
        double longitude = payload.getLongitude();
        String date = payload.getDate();

        Double temperature = getTemperatureFromDatabase(latitude, longitude, date);

        if (temperature != null) {
            response.setContentType("application/json");
            response.setCharacterEncoding("UTF-8");
            gson.toJson(new ResponsePayload(temperature), response.getWriter());
        } else {
            response.setStatus(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private Double getTemperatureFromDatabase(double latitude, double longitude, String date) {
        String query = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setString(3, date);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    private static class RequestPayload {
        private double latitude;
        private double longitude;
        private String date;

        public double getLatitude() {
            return latitude;
        }

        public double getLongitude() {
            return longitude;
        }

        public String getDate() {
            return date;
        }
    }

    private static class ResponsePayload {
        private Double temperature;

        public ResponsePayload(Double temperature) {
            this.temperature = temperature;
        }
    }
}