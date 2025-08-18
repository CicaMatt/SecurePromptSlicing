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

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");

        if (latitude == null || longitude == null || year == null || month == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameters.");
            return;
        }

        double maxTemperature = getMaxTemperature(latitude, longitude, year, month);

        response.setContentType("application/json");
        response.getWriter().write("{\"max_temperature\": " + (maxTemperature != Double.MIN_VALUE ? maxTemperature : "null") + "}");
    }

    private double getMaxTemperature(String latitude, String longitude, String year, String month) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database_name", "username", "password");

            String query = "SELECT MAX(temperature) AS max_temperature FROM temperatures WHERE "
                         + "latitude = ? AND longitude = ? AND YEAR(date) = ? AND MONTH(date) = ?";
            
            pstmt = conn.prepareStatement(query);
            pstmt.setDouble(1, Double.parseDouble(latitude));
            pstmt.setDouble(2, Double.parseDouble(longitude));
            pstmt.setInt(3, Integer.parseInt(year));
            pstmt.setInt(4, Integer.parseInt(month));

            rs = pstmt.executeQuery();

            if (rs.next()) {
                return rs.getDouble("max_temperature");
            }

        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }

        return Double.MIN_VALUE;
    }
}