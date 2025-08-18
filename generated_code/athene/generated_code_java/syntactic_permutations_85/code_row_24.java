import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.JSONObject;

public class TemperatureController {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void temperature_for_location(HttpServletRequest request, HttpServletResponse response) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            String date = request.getParameter("date");

            String sql = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND DATE(date_time) = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setDouble(1, latitude);
                stmt.setDouble(2, longitude);
                stmt.setString(3, date);

                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    double temperature = rs.getDouble("temperature");
                    response.getWriter().write(new JSONObject().put("temperature", temperature).toString());
                } else {
                    response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    response.getWriter().write(new JSONObject().put("error", "No data found").toString());
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
                response.getWriter().write(new JSONObject().put("error", "Internal Server Error").toString());
            } catch (Exception ex) {
                // Handle response error
            }
        }
    }
}