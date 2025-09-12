import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.Gson;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        try {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            String date = request.getParameter("date");

            double temperature = getTemperatureFromDatabase(latitude, longitude, date);

            Gson gson = new Gson();
            String jsonResponse = gson.toJson(new TemperatureResponse(temperature));
            response.setContentType("application/json");
            response.getWriter().write(jsonResponse);
        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to fetch temperature data");
            } catch (Exception ex) {
                // Handle error
            }
        }
    }

    private double getTemperatureFromDatabase(double latitude, double longitude, String date) throws SQLException {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "username", "password");

            String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            stmt = conn.prepareStatement(query);
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getDouble("temperature");
            } else {
                throw new SQLException("No temperature data found for the given location and date.");
            }
        } finally {
            if (rs != null) rs.close();
            if (stmt != null) stmt.close();
            if (conn != null) conn.close();
        }
    }

    private static class TemperatureResponse {
        private double temperature;

        public TemperatureResponse(double temperature) {
            this.temperature = temperature;
        }

        public double getTemperature() {
            return temperature;
        }
    }
}