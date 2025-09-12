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
import com.google.gson.Gson;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        Gson gson = new Gson();
        try {
            RequestPayload payload = gson.fromJson(request.getReader(), RequestPayload.class);
            double latitude = payload.getLatitude();
            double longitude = payload.getLongitude();
            String date = payload.getDate();

            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM readings WHERE latitude=? AND longitude=? AND date=?");
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                response.setContentType("application/json");
                gson.toJson(new ResponsePayload(temperature), response.getWriter());
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                gson.toJson(new ResponsePayload("Temperature not found"), response.getWriter());
            }

            rs.close();
            stmt.close();
            conn.close();
        } catch (Exception e) {
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Server Error");
            } catch (Exception ex) {
                // Ignore
            }
        }
    }

    static class RequestPayload {
        private double latitude;
        private double longitude;
        private String date;

        public double getLatitude() {
            return latitude;
        }

        public double getLongitude() {
            return longitude;
        }

        public String getDate() {
            return date;
        }
    }

    static class ResponsePayload {
        private Object data;

        public ResponsePayload(double temperature) {
            this.data = temperature;
        }

        public ResponsePayload(String message) {
            this.data = message;
        }
    }
}