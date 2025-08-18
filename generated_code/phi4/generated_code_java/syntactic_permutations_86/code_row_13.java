import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class TemperatureServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        if (latitude == null || longitude == null || year == null || month == null || day == null || gribFile == null) {
            out.println("<h1>Error: All parameters must be provided</h1>");
            return;
        }

        String maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);

        if (maxTemperature != null) {
            out.println("<html><body>");
            out.println("<h1>Maximum Temperature: " + maxTemperature + "</h1>");
            out.println("</body></html>");
        } else {
            out.println("<h1>Error: Unable to retrieve maximum temperature</h1>");
        }
    }

    private String getMaxTemperature(String latitude, String longitude, String year, String month, String day, String gribFile) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "SELECT MAX(temperature) AS max_temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, latitude);
            pstmt.setString(2, longitude);
            pstmt.setInt(3, Integer.parseInt(year));
            pstmt.setInt(4, Integer.parseInt(month));
            pstmt.setInt(5, Integer.parseInt(day));
            pstmt.setString(6, gribFile);

            rs = pstmt.executeQuery();

            if (rs.next()) {
                return rs.getString("max_temperature");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try { if (rs != null) rs.close(); } catch (SQLException e) { e.printStackTrace(); }
            try { if (pstmt != null) pstmt.close(); } catch (SQLException e) { e.printStackTrace(); }
            try { if (conn != null) conn.close(); } catch (SQLException e) { e.printStackTrace(); }
        }

        return null;
    }
}


Make sure to replace `your_database`, `root`, and `password` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is included in your project's classpath.