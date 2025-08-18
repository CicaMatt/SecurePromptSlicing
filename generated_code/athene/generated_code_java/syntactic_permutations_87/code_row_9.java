import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.JSONObject;

public class TemperatureServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/weatherdb", "user", "password")) {
            String sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, latitude);
            stmt.setString(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                JSONObject json = new JSONObject().put("temperature", temperature);
                response.setContentType("application/json");
                response.getWriter().write(json.toString());
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("No data found for the given location and date.");
            }
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }
}