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

    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String date = request.getParameter("date");
            double temperature = getTemperatureForDate(conn, date);
            Gson gson = new Gson();
            String json = gson.toJson(new TemperatureResponse(temperature));
            response.setContentType("application/json");
            response.getWriter().write(json);
        } catch (SQLException e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Database error occurred.");
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }

    private double getTemperatureForDate(Connection conn, String date) throws SQLException {
        String sql = "SELECT temperature FROM measurements WHERE date = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, date);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getDouble("temperature");
            }
        }
        return -999.0; // Return a specific value for not found
    }

    private static class TemperatureResponse {
        private double temperature;

        public TemperatureResponse(double temperature) {
            this.temperature = temperature;
        }
    }
}