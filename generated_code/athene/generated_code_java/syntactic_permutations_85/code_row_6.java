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

@WebServlet("/api/")
public class TemperatureServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        try {
            String payload = request.getReader().lines().reduce("", (accumulator, actual) -> accumulator + actual);
            Gson gson = new Gson();
            Data data = gson.fromJson(payload, Data.class);

            double latitude = data.getLatitude();
            double longitude = data.getLongitude();
            String date = data.getDate();

            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "user", "password");
            PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM measurements WHERE latitude = ? AND longitude = ? AND date = ?");
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            double temperature = -999.0; // Default value if no data found
            if (rs.next()) {
                temperature = rs.getDouble("temperature");
            }

            rs.close();
            stmt.close();
            conn.close();

            TemperatureResult result = new TemperatureResult(temperature);
            String jsonResult = gson.toJson(result);
            response.setContentType("application/json");
            response.getWriter().write(jsonResult);

        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while processing the request.");
            } catch (SQLException | java.io.IOException ex) {
                // Handle exception
            }
        }
    }

    static class Data {
        private double latitude;
        private double longitude;
        private String date;

        public double getLatitude() { return latitude; }
        public double getLongitude() { return longitude; }
        public String getDate() { return date; }
    }

    static class TemperatureResult {
        private double temperature;

        public TemperatureResult(double temperature) {
            this.temperature = temperature;
        }

        public double getTemperature() {
            return temperature;
        }
    }
}