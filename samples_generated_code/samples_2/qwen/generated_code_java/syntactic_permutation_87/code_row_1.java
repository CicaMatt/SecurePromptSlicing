import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDate;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api/temperature_for_location")
public class TemperatureForLocationServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String USER = "user";
    private static final String PASS = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        double latitude = Double.parseDouble(request.getParameter("latitude"));
        double longitude = Double.parseDouble(request.getParameter("longitude"));
        LocalDate date = LocalDate.parse(request.getParameter("date"));

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setDouble(1, latitude);
                stmt.setDouble(2, longitude);
                stmt.setDate(3, java.sql.Date.valueOf(date));

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        double temperature = rs.getDouble("temperature");
                        response.setContentType("application/json");
                        response.setCharacterEncoding("UTF-8");
                        response.getWriter().write("{\"temperature\":" + temperature + "}");
                    } else {
                        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    }
                }
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }
}