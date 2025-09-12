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
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Gson gson = new Gson();
        RequestPayload payload = gson.fromJson(request.getReader(), RequestPayload.class);
        
        double latitude = payload.getLatitude();
        double longitude = payload.getLongitude();
        String date = payload.getDate();

        double temperature = getTemperatureFromDatabase(latitude, longitude, date);

        response.setContentType("application/json");
        response.getWriter().write("{\"temperature\": " + temperature + "}");
    }

    private double getTemperatureFromDatabase(double latitude, double longitude, String date) {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "root";
        String password = "password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setDouble(1, latitude);
                preparedStatement.setDouble(2, longitude);
                preparedStatement.setString(3, date);

                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next()) {
                        return resultSet.getDouble("temperature");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Double.NaN;
    }

    private static class RequestPayload {
        private double latitude;
        private double longitude;
        private String date;

        public double getLatitude() {
            return latitude;
        }

        public void setLatitude(double latitude) {
            this.latitude = latitude;
        }

        public double getLongitude() {
            return longitude;
        }

        public void setLongitude(double longitude) {
            this.longitude = longitude;
        }

        public String getDate() {
            return date;
        }

        public void setDate(String date) {
            this.date = date;
        }
    }
}