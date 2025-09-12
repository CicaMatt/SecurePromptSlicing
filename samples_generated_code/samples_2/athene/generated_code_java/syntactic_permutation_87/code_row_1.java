import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/weatherdb", "user", "password")) {
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, latitude);
                pstmt.setString(2, longitude);
                pstmt.setString(3, date);

                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next()) {
                        double temperature = rs.getDouble("temperature");
                        response.getWriter().write(String.valueOf(temperature));
                    } else {
                        response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given location and date.");
                    }
                }
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while processing your request.");
        }
    }
}