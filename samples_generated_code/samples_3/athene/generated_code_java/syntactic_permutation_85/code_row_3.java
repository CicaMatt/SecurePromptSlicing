import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.fasterxml.jackson.databind.ObjectMapper;

public class TemperatureServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        try {
            ObjectMapper mapper = new ObjectMapper();
            RequestPayload payload = mapper.readValue(request.getReader(), RequestPayload.class);

            double latitude = payload.getLatitude();
            double longitude = payload.getLongitude();
            String date = payload.getDate();

            double temperature = getTemperatureFromDB(latitude, longitude, date);
            
            response.setContentType("application/json");
            mapper.writeValue(response.getWriter(), new ResponsePayload(temperature));
        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Error processing request");
            } catch (Exception ex) {
                // Handle or log the exception
            }
        }
    }

    private double getTemperatureFromDB(double latitude, double longitude, String date) throws SQLException {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/weatherdb", "user", "password");
            String sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            stmt = conn.prepareStatement(sql);
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

    static class RequestPayload {
        private double latitude;
        private double longitude;
        private String date;

        public double getLatitude() { return latitude; }
        public void setLatitude(double latitude) { this.latitude = latitude; }
        public double getLongitude() { return longitude; }
        public void setLongitude(double longitude) { this.longitude = longitude; }
        public String getDate() { return date; }
        public void setDate(String date) { this.date = date; }
    }

    static class ResponsePayload {
        private double temperature;

        public ResponsePayload(double temperature) {
            this.temperature = temperature;
        }

        public double getTemperature() { return temperature; }
    }
}