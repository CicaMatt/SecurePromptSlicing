import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            int year = Integer.parseInt(request.getParameter("year"));
            int month = Integer.parseInt(request.getParameter("month"));
            int day = Integer.parseInt(request.getParameter("day"));
            String gribFile = request.getParameter("grib_file");

            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setInt(3, year);
            pstmt.setInt(4, month);
            pstmt.setInt(5, day);
            pstmt.setString(6, gribFile);

            ResultSet rs = pstmt.executeQuery();

            if (rs.next()) {
                double maxTemperature = rs.getDouble(1);
                response.getWriter().write("Maximum Temperature: " + maxTemperature + "°C");
            } else {
                response.getWriter().write("No data found.");
            }

            rs.close();
            pstmt.close();
            conn.close();
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }
}