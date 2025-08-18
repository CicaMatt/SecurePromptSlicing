import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemperatureServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        try {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            String date = request.getParameter("date");

            TemperatureResponse tempResponse = temperatureForLocation(latitude, longitude, date);
            
            response.setContentType("application/json");
            response.getWriter().write(tempResponse.toJson());
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            try {
                response.getWriter().write("{\"error\":\"" + e.getMessage() + "\"}");
            } catch (Exception ex) {}
        }
    }

    private TemperatureResponse temperatureForLocation(double latitude, double longitude, String date) throws SQLException {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            
            String sql = "SELECT temperature FROM SensorData WHERE latitude = ? AND longitude = ? AND date = ?";
            stmt = conn.prepareStatement(sql);
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            rs = stmt.executeQuery();

            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                return new TemperatureResponse(temperature);
            } else {
                throw new SQLException("No data found for given location and date.");
            }
        } finally {
            if (rs != null) rs.close();
            if (stmt != null) stmt.close();
            if (conn != null) conn.close();
        }
    }

    private static class TemperatureResponse {
        private final double temperature;

        public TemperatureResponse(double temperature) {
            this.temperature = temperature;
        }

        public String toJson() {
            return "{\"temperature\":" + temperature + "}";
        }
    }
}