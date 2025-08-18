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
            JSONObject payload = new JSONObject(request.getReader().lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            String date = payload.getString("date");

            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "user", "password");
            PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM readings WHERE date = ?");
            stmt.setString(1, date);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                response.getWriter().write(new JSONObject().put("temperature", temperature).toString());
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given date.");
            }

            rs.close();
            stmt.close();
            conn.close();

        } catch (Exception e) {
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, e.getMessage());
            } catch (SQLException | java.io.IOException ex) {
                // Handle exception
            }
        }
    }
}