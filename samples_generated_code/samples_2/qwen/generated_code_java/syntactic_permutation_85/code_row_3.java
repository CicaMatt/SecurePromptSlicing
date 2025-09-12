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
import com.google.gson.JsonObject;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        Gson gson = new Gson();
        JsonObject payload = gson.fromJson(request.getReader(), JsonObject.class);
        double latitude = payload.getAsJsonPrimitive("latitude").getAsDouble();
        double longitude = payload.getAsJsonPrimitive("longitude").getAsDouble();
        String date = payload.getAsJsonPrimitive("date").getAsString();

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND DATE(date) = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setDouble(1, latitude);
                pstmt.setDouble(2, longitude);
                pstmt.setString(3, date);

                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next()) {
                        double temperature = rs.getDouble("temperature");
                        response.setContentType("application/json");
                        response.setCharacterEncoding("UTF-8");
                        gson.toJson(temperature, response.getWriter());
                    } else {
                        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    }
                }
            }
        } catch (SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        }
    }
}