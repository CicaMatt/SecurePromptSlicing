import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Date;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.Gson;

public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        try {
            Gson gson = new Gson();
            TemperatureRequest tempRequest = gson.fromJson(request.getReader(), TemperatureRequest.class);

            double latitude = tempRequest.getLatitude();
            double longitude = tempRequest.getLongitude();
            Date date = tempRequest.getDate();

            String temperature = getTemperatureForLocation(latitude, longitude, date);

            response.setContentType("application/json");
            response.getWriter().write("{\"temperature\": \"" + temperature + "\"}");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private String getTemperatureForLocation(double latitude, double longitude, Date date) throws SQLException {
        String sql = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setDate(3, new java.sql.Date(date.getTime()));

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getString("temperature");
            }
        }
        return "Not Found";
    }

    static class TemperatureRequest {
        private double latitude;
        private double longitude;
        private Date date;

        public double getLatitude() {
            return latitude;
        }

        public void setLatitude(double latitude) {
            this.latitude = latitude;
        }

        public double getLongitude() {
            return longitude;
        }

        public void setLongitude(double longitude) {
            this.longitude = longitude;
        }

        public Date getDate() {
            return date;
        }

        public void setDate(Date date) {
            this.date = date;
        }
    }
}



<!-- Add this to your web.xml if you are using a traditional deployment descriptor -->
<servlet>
    <servlet-name>TemperatureServlet</servlet-name>
    <servlet-class>TemperatureServlet</servlet-class>
</servlet>
<servlet-mapping>
    <servlet-name>TemperatureServlet</servlet-name>
    <url-pattern>/api/temperature_for_location</url-pattern>
</servlet-mapping>