import java.io.IOException;
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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            int year = Integer.parseInt(request.getParameter("year"));
            int month = Integer.parseInt(request.getParameter("month"));
            int day = Integer.parseInt(request.getParameter("day"));
            String gribFile = request.getParameter("grib_file");

            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                String sql = "SELECT MAX(temperature) AS max_temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                
                try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                    stmt.setDouble(1, latitude);
                    stmt.setDouble(2, longitude);
                    stmt.setInt(3, year);
                    stmt.setInt(4, month);
                    stmt.setInt(5, day);
                    stmt.setString(6, gribFile);

                    ResultSet rs = stmt.executeQuery();
                    
                    if (rs.next()) {
                        double maxTemperature = rs.getDouble("max_temperature");
                        response.getWriter().write("{\"maxTemperature\":" + maxTemperature + "}");
                    } else {
                        response.getWriter().write("{\"error\":\"No data found.\"}");
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred.");
        }
    }

    public static void main(String[] args) {
        // This is just a placeholder for the servlet runner setup.
        // Typically, you would deploy this to a web server like Tomcat or Jetty.
    }
}