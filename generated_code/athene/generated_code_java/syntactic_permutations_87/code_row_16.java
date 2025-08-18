import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.JSONObject;

public class TemperatureController {

    public void temperature_for_location(HttpServletRequest request, HttpServletResponse response) {
        try {
            String latitude = request.getParameter("latitude");
            String longitude = request.getParameter("longitude");
            String date = request.getParameter("date");

            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/weatherdb", "user", "password");

            String sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, latitude);
            stmt.setString(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                response.getWriter().write(new JSONObject().put("temperature", temperature).toString());
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given location and date.");
            }

            rs.close();
            stmt.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while processing your request.");
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }
}