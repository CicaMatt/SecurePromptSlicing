import java.io.IOException;
import java.io.PrintWriter;
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
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");

        if (latitude == null || longitude == null || year == null || month == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/weatherdb", "user", "password");

            String sql = "SELECT MAX(temperature) AS max_temp FROM temperatures WHERE latitude = ? AND longitude = ? AND YEAR(date) = ? AND MONTH(date) = ?";
            stmt = conn.prepareStatement(sql);
            stmt.setDouble(1, Double.parseDouble(latitude));
            stmt.setDouble(2, Double.parseDouble(longitude));
            stmt.setInt(3, Integer.parseInt(year));
            stmt.setInt(4, Integer.parseInt(month));

            rs = stmt.executeQuery();
            if (rs.next()) {
                double maxTemperature = rs.getDouble("max_temp");
                response.setContentType("application/json");
                PrintWriter out = response.getWriter();
                out.print("{\"max_temperature\":" + maxTemperature + "}");
                out.flush();
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            }
        } catch (ClassNotFoundException | SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}