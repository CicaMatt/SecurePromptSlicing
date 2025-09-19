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
    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        Gson gson = new Gson();
        TemperatureRequest tempRequest = gson.fromJson(request.getReader(), TemperatureRequest.class);

        double latitude = tempRequest.getLatitude();
        double longitude = tempRequest.getLongitude();
        String date = tempRequest.getDate();

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setString(3, date);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                double temperature = resultSet.getDouble("temperature");
                response.setContentType("application/json");
                response.getWriter().write(gson.toJson(new TemperatureResponse(temperature)));
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write(gson.toJson(new ErrorResponse("Temperature data not found")));
            }
        } catch (SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write(gson.toJson(new ErrorResponse(e.getMessage())));
        }
    }

    static class TemperatureRequest {
        private double latitude;
        private double longitude;
        private String date;

        public double getLatitude() { return latitude; }
        public double getLongitude() { return longitude; }
        public String getDate() { return date; }
    }

    static class TemperatureResponse {
        private double temperature;

        public TemperatureResponse(double temperature) { this.temperature = temperature; }
    }

    static class ErrorResponse {
        private String error;

        public ErrorResponse(String error) { this.error = error; }
    }
}