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
        try {
            String latitude = request.getParameter("latitude");
            String longitude = request.getParameter("longitude");
            String date = request.getParameter("date");

            double temperature = getTemperatureFromDatabase(latitude, longitude, date);

            Gson gson = new Gson();
            String json = gson.toJson(new TemperatureResponse(temperature));
            response.setContentType("application/json");
            response.getWriter().write(json);
        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to fetch temperature");
            } catch (Exception ex) {
                // Handle exception
            }
        }
    }

    private double getTemperatureFromDatabase(String latitude, String longitude, String date) throws SQLException {
        double temperature = 0.0;
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "user", "password")) {
            String sql = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, latitude);
                stmt.setString(2, longitude);
                stmt.setString(3, date);

                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    temperature = rs.getDouble("temperature");
                }
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return temperature;
    }

    private static class TemperatureResponse {
        private double temperature;

        public TemperatureResponse(double temperature) {
            this.temperature = temperature;
        }
    }
}