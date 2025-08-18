import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.time.LocalDate;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.json.JSONObject;

public class TemperatureController {

    public void temperature_for_location(HttpServletRequest request, HttpServletResponse response) {
        try {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            LocalDate date = LocalDate.parse(request.getParameter("date"));

            String url = "jdbc:mysql://localhost:3306/weather_db";
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (Connection conn = DriverManager.getConnection(url, "user", "password");
                 PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setDouble(1, latitude);
                stmt.setDouble(2, longitude);
                stmt.setDate(3, java.sql.Date.valueOf(date));

                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    double temperature = rs.getDouble("temperature");
                    response.getWriter().write(new JSONObject().put("temperature", temperature).toString());
                } else {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given location and date.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while processing your request.");
            } catch (Exception ex) {
                // handle exception
            }
        }
    }
}