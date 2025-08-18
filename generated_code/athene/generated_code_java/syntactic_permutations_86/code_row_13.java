import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/getMaxTemperature")
public class MaxTemperatureServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String grib_file = request.getParameter("grib_file");

        try (Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourdatabase", "username", "password")) {
            String sql = "SELECT MAX(temperature) AS max_temperature FROM weather_data "
                       + "WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, latitude);
                pstmt.setString(2, longitude);
                pstmt.setString(3, year);
                pstmt.setString(4, month);
                pstmt.setString(5, day);
                pstmt.setString(6, grib_file);

                ResultSet rs = pstmt.executeQuery();
                if (rs.next()) {
                    double maxTemperature = rs.getDouble("max_temperature");
                    response.getWriter().write("Max Temperature: " + maxTemperature);
                } else {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given parameters.");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Database error occurred.");
        }
    }
}