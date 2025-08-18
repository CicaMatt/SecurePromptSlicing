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
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        double temperature = getTemperatureFromDatabase(latitude, longitude, date);

        try {
            response.setContentType("application/json");
            JSONObject json = new JSONObject();
            json.put("temperature", temperature);
            response.getWriter().write(json.toString());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private double getTemperatureFromDatabase(String latitude, String longitude, String date) {
        String url = "jdbc:mysql://localhost:3306/yourdb";
        String user = "username";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement ps = conn.prepareStatement(query)) {
                ps.setString(1, latitude);
                ps.setString(2, longitude);
                ps.setString(3, date);
                try (ResultSet rs = ps.executeQuery()) {
                    if (rs.next()) {
                        return rs.getDouble("temperature");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -999.0; // Return a default value or handle error as needed
    }
}