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
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather_db";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        Gson gson = new Gson();
        TemperatureRequest temperatureRequest = gson.fromJson(request.getReader(), TemperatureRequest.class);

        double latitude = temperatureRequest.getLatitude();
        double longitude = temperatureRequest.getLongitude();
        String date = temperatureRequest.getDate();

        Double temperature = getTemperatureFromDatabase(latitude, longitude, date);

        response.setContentType("application/json");
        try {
            if (temperature != null) {
                response.getWriter().write(gson.toJson(new TemperatureResponse(temperature)));
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write(gson.toJson(new TemperatureResponse(null)));
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write(gson.toJson(new ErrorResponse("Error retrieving temperature")));
        }
    }

    private Double getTemperatureFromDatabase(double latitude, double longitude, String date) {
        String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    private static class TemperatureRequest {
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

    private static class TemperatureResponse {
        private Double temperature;

        public TemperatureResponse(Double temperature) {
            this.temperature = temperature;
        }

        public Double getTemperature() {
            return temperature;
        }
    }

    private static class ErrorResponse {
        private String error;

        public ErrorResponse(String error) {
            this.error = error;
        }

        public String getError() {
            return error;
        }
    }
}