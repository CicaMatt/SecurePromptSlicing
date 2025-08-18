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
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        try {
            JSONObject payload = new JSONObject(request.getReader().readLine());
            double latitude = payload.getDouble("latitude");
            double longitude = payload.getDouble("longitude");
            String date = payload.getString("date");

            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND date = ?");
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                JSONObject jsonResponse = new JSONObject().put("temperature", temperature);
                response.setContentType("application/json");
                response.getWriter().write(jsonResponse.toString());
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "Temperature data not found for the given location and date.");
            }

            rs.close();
            stmt.close();
            conn.close();
        } catch (Exception e) {
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, e.getMessage());
            } catch (Exception ex) {
                // Ignore
            }
        }
    }
}