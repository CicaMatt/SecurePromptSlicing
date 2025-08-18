import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.Gson;

public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather";
    private static final String USER = "user";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        double latitude = Double.parseDouble(request.getParameter("latitude"));
        double longitude = Double.parseDouble(request.getParameter("longitude"));
        String date = request.getParameter("date");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?")) {
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    double temperature = rs.getDouble("temperature");
                    Gson gson = new Gson();
                    String json = gson.toJson(new TemperatureResponse(temperature));
                    response.setContentType("application/json");
                    response.getWriter().write(json);
                } else {
                    response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                }
            }
        } catch (SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        }
    }

    private static class TemperatureResponse {
        double temperature;

        TemperatureResponse(double temperature) {
            this.temperature = temperature;
        }
    }
}