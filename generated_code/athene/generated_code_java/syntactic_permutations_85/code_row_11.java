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

    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        double temperature = getTemperatureFromDB(latitude, longitude, date);

        Gson gson = new Gson();
        String json = gson.toJson(new TemperatureResponse(temperature));
        try {
            response.getWriter().write(json);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private double getTemperatureFromDB(String latitude, String longitude, String date) {
        String sql = "SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ? AND date = ?";
        double temperature = 0.0;

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "user", "password");
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setString(1, latitude);
            stmt.setString(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                temperature = rs.getDouble("temperature");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return temperature;
    }

    static class TemperatureResponse {
        double temperature;

        public TemperatureResponse(double temperature) {
            this.temperature = temperature;
        }
    }
}