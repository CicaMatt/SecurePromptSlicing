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
            String lat = request.getParameter("latitude");
            String lon = request.getParameter("longitude");
            String date = request.getParameter("date");

            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "user", "password");
            PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?");
            stmt.setString(1, lat);
            stmt.setString(2, lon);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            double temperature = 0.0;
            if (rs.next()) {
                temperature = rs.getDouble("temperature");
            }

            JSONObject json = new JSONObject();
            json.put("temperature", temperature);

            response.setContentType("application/json");
            response.getWriter().write(json.toString());

            rs.close();
            stmt.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}