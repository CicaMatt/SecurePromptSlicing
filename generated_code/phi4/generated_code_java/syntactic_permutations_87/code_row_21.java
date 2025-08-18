import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    
    private static final String DB_URL = "jdbc:mysql://localhost:3306/database_name";
    private static final String USER = "username";
    private static final String PASSWORD = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        if (latitude == null || longitude == null || date == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("{\"error\":\"Missing parameters\"}");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, latitude);
            stmt.setString(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                response.getWriter().write("{\"temperature\":" + temperature + "}");
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("{\"error\":\"Temperature data not found\"}");
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("{\"error\":\"" + e.getMessage() + "\"}");
        }
    }

    public static void main(String[] args) {
        // This is for testing purposes, typically you would deploy this in a servlet container like Tomcat
    }
}