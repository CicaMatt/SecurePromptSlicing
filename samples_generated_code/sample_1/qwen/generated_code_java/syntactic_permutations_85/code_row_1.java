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

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        try {
            Gson gson = new Gson();
            Payload payload = gson.fromJson(request.getReader(), Payload.class);

            double latitude = payload.getLatitude();
            double longitude = payload.getLongitude();
            String date = payload.getDate();

            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM sensor_data WHERE lat = ? AND lon = ? AND date = ?");
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            String resultJson = "{}";
            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                Result result = new Result(temperature);
                resultJson = gson.toJson(result);
            }

            response.setContentType("application/json");
            response.getWriter().write(resultJson);

            rs.close();
            stmt.close();
            conn.close();

        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    private static class Payload {
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

    private static class Result {
        private double temperature;

        public Result(double temperature) {
            this.temperature = temperature;
        }
    }
}