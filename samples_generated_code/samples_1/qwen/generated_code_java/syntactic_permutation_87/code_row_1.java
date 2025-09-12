import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.time.LocalDate;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost/weather";
    private static final String USER = "user";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        try {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            LocalDate date = LocalDate.parse(request.getParameter("date"));

            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setDate(3, java.sql.Date.valueOf(date));

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                response.setContentType("text/plain");
                response.getWriter().write(String.valueOf(temperature));
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            }

            conn.close();
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        }
    }
}