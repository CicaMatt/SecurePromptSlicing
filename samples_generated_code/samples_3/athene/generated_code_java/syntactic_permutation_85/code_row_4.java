import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.Gson;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        try {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            String date = request.getParameter("date");

            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT temperature FROM measurements WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            double temperature = 0;
            if (rs.next()) {
                temperature = rs.getDouble("temperature");
            }

            rs.close();
            stmt.close();
            conn.close();

            response.setContentType("application/json");
            new Gson().toJson(new TemperatureResponse(temperature), response.getWriter());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    static class TemperatureResponse {
        double temperature;

        public TemperatureResponse(double temperature) {
            this.temperature = temperature;
        }
    }
}