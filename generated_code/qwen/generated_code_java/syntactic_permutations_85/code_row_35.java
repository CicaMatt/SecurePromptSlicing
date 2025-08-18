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
public class Sensor extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Gson gson = new Gson();
        RequestPayload payload = gson.fromJson(request.getReader(), RequestPayload.class);
        
        double latitude = payload.latitude;
        double longitude = payload.longitude;
        String date = payload.date;
        
        Double temperature = getTemperatureFromDatabase(latitude, longitude, date);
        
        response.setContentType("application/json");
        response.getWriter().write("{\"temperature\": " + (temperature != null ? temperature : "null") + "}");
    }
    
    private Double getTemperatureFromDatabase(double latitude, double longitude, String date) {
        String url = "jdbc:mysql://localhost:3306/weatherdb";
        String user = "user";
        String password = "password";
        
        String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
        
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            
            stmt.setDouble(1, latitude);
            stmt.setDouble(2, longitude);
            stmt.setString(3, date);
            
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }
    
    private static class RequestPayload {
        double latitude;
        double longitude;
        String date;
    }
}