import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.JSONObject;

public class TemperatureController {

    public void temperature_for_location(HttpServletRequest request, HttpServletResponse response) {
        try {
            JSONObject payload = new JSONObject(request.getParameter("payload"));
            double latitude = payload.getDouble("latitude");
            double longitude = payload.getDouble("longitude");
            String date = payload.getString("date");

            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "user", "password");
            PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?");
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            double temperature = 0.0;
            if (rs.next()) {
                temperature = rs.getDouble("temperature");
            }

            JSONObject result = new JSONObject().put("temperature", temperature);
            response.getWriter().write(result.toString());

            rs.close();
            stmt.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}