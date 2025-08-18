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

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        if (latitude == null || longitude == null || date == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameters");
            return;
        }

        double temp = getTemperatureForLocation(latitude, longitude, date);
        Gson gson = new Gson();
        String jsonResponse = gson.toJson(temp);

        response.setContentType("application/json");
        response.getWriter().write(jsonResponse);
    }

    private double getTemperatureForLocation(String latitude, String longitude, String date) {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "root"; // change to your database username
        String password = ""; // change to your database password

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?")) {

            stmt.setDouble(1, Double.parseDouble(latitude));
            stmt.setDouble(2, Double.parseDouble(longitude));
            stmt.setString(3, date);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getDouble("temperature");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return -999.0; // Return a sentinel value indicating an error
    }
}