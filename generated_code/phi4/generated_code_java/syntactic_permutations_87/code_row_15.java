import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather";
    private static final String USER = "root";
    private static final String PASS = "";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        try {
            String latitude = request.getParameter("latitude");
            String longitude = request.getParameter("longitude");
            String date = request.getParameter("date");

            if (latitude == null || longitude == null || date == null) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Missing parameters");
                return;
            }

            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String query = "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            
            stmt.setString(1, latitude);
            stmt.setString(2, longitude);
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                response.getWriter().write(String.valueOf(temperature));
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("No data found for the given location and date.");
            }

            rs.close();
            stmt.close();
            conn.close();

        } catch (Exception e) {
            throw new ServletException(e);
        }
    }
}