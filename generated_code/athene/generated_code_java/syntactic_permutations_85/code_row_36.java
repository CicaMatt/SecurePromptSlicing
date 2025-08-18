import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.JSONObject;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        try {
            String payload = request.getParameter("payload");
            JSONObject jsonPayload = new JSONObject(payload);
            double latitude = jsonPayload.getDouble("latitude");
            double longitude = jsonPayload.getDouble("longitude");
            String date = jsonPayload.getString("date");

            double temperature = getTemperatureFromDB(latitude, longitude, date);

            response.setContentType("application/json");
            response.getWriter().write("{\"temperature\": " + temperature + "}");
        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while processing the request.");
            } catch (SQLException | SQLException ex) {
                ex.printStackTrace();
            }
        }
    }

    private double getTemperatureFromDB(double latitude, double longitude, String date) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/temperature_db";
        String user = "user";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setDouble(1, latitude);
                stmt.setDouble(2, longitude);
                stmt.setString(3, date);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        return rs.getDouble("temperature");
                    }
                }
            }
        }
        throw new SQLException("No temperature data found for the given location and date.");
    }
}