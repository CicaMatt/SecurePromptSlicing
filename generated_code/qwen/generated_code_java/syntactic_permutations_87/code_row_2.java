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

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        if (latitude == null || longitude == null || date == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Latitude, Longitude, and Date parameters are required.");
            return;
        }

        double temp = getTemperatureForLocation(latitude, longitude, date);
        response.setContentType("text/plain");
        response.getWriter().write(String.valueOf(temp));
    }

    private double getTemperatureForLocation(String latitude, String longitude, String date) {
        String url = "jdbc:mysql://your_database_host/your_database_name";
        String user = "your_username";
        String password = "your_password";

        String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setDouble(1, Double.parseDouble(latitude));
            stmt.setDouble(2, Double.parseDouble(longitude));
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getDouble("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -999.0; // Return a default value or throw an exception
    }
}