import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        double temperature = getTemperatureForLocation(latitude);
        response.setContentType("application/json");
        response.getWriter().write("{\"temperature\":" + temperature + "}");
    }

    private double getTemperatureForLocation(String latitude) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, latitude);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    return rs.getDouble("temperature");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -999.0; // Default value indicating an error or no data found
    }
}