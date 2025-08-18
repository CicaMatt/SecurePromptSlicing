import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.JSONObject;

public class TemperatureService {

    public void temperature_for_location(HttpServletRequest request, HttpServletResponse response) {
        try {
            String latitude = request.getParameter("latitude");
            if (latitude == null || latitude.isEmpty()) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                return;
            }

            double latValue = Double.parseDouble(latitude);
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/weatherdb", "user", "password");
            PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM weather_data WHERE latitude = ?");
            stmt.setDouble(1, latValue);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double temp = rs.getDouble("temperature");
                JSONObject json = new JSONObject().put("temperature", temp);
                response.getWriter().write(json.toString());
                response.setStatus(HttpServletResponse.SC_OK);
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            }

            rs.close();
            stmt.close();
            conn.close();
        } catch (SQLException | NumberFormatException e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Database or input error");
            } catch (Exception ex) {
                // Handle exception
            }
        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "General error");
            } catch (Exception ex) {
                // Handle exception
            }
        }
    }
}