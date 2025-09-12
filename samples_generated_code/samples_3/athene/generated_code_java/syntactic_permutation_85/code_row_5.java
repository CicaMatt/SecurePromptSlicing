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
        try {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            String date = request.getParameter("date");

            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            double temperature = -999; // Default value if not found
            if (rs.next()) {
                temperature = rs.getDouble("temperature");
            }

            JSONObject json = new JSONObject();
            json.put("latitude", latitude);
            json.put("longitude", longitude);
            json.put("date", date);
            json.put("temperature", temperature);

            response.setContentType("application/json");
            response.getWriter().write(json.toString());

            rs.close();
            stmt.close();
            conn.close();
        } catch (SQLException | NumberFormatException e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Database error or invalid input.");
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }
}