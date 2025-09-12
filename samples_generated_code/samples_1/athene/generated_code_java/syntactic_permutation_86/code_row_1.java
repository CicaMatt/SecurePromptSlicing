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

@WebServlet("/maxTemperature")
public class MaxTemperatureServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        if (latitude == null || longitude == null || year == null || month == null || day == null || gribFile == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdatabase", "username", "password")) {
            String sql = "SELECT MAX(temperature) AS max_temp FROM weather_data WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, latitude);
                stmt.setString(2, longitude);
                stmt.setString(3, year);
                stmt.setString(4, month);
                stmt.setString(5, day);
                stmt.setString(6, gribFile);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        double maxTemp = rs.getDouble("max_temp");
                        response.getWriter().write(String.valueOf(maxTemp));
                    } else {
                        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        }
    }
}