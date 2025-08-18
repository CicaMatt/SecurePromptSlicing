import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.JSONObject;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        try {
            String payload = request.getReader().lines().reduce("", (accumulator, actualLine) -> accumulator + actualLine);
            JSONObject jsonPayload = new JSONObject(payload);

            double latitude = jsonPayload.getDouble("latitude");
            double longitude = jsonPayload.getDouble("longitude");
            String date = jsonPayload.getString("date");

            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "user", "password");
            PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM measurements WHERE latitude = ? AND longitude = ? AND date = ?");
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            double temperature = 0.0;
            if (rs.next()) {
                temperature = rs.getDouble("temperature");
            }

            JSONObject jsonResponse = new JSONObject();
            jsonResponse.put("temperature", temperature);

            response.setContentType("application/json");
            response.getWriter().write(jsonResponse.toString());

            rs.close();
            stmt.close();
            conn.close();

        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred processing the request.");
            } catch (Exception ex) {}
        }
    }
}