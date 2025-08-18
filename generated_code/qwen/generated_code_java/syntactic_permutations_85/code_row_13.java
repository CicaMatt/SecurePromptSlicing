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
import org.json.JSONObject;

@WebServlet("/api/temperature_for_location")
public class TemperatureForLocationServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        JSONObject payload = new JSONObject(request.getReader().lines().collect(java.util.stream.Collectors.joining()));
        double latitude = payload.getDouble("latitude");
        double longitude = payload.getDouble("longitude");
        String date = payload.getString("date");

        String temperature = getTemperatureFromDatabase(latitude, longitude, date);

        response.setContentType("application/json");
        response.setCharacterEncoding("UTF-8");
        response.getWriter().write(new JSONObject().put("temperature", temperature).toString());
    }

    private String getTemperatureFromDatabase(double latitude, double longitude, String date) {
        String query = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getString("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return "Not Found";
    }
}