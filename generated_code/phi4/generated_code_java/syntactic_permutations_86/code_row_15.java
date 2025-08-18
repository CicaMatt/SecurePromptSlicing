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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        if (latitude == null || longitude == null || year == null || month == null || 
            day == null || gribFile == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameters");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT MAX(temperature) AS max_temperature FROM temperature_data " +
                         "WHERE latitude = ? AND longitude = ? AND year = ? " +
                         "AND month = ? AND day = ? AND grib_file = ?";
                         
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, latitude);
                stmt.setString(2, longitude);
                stmt.setInt(3, Integer.parseInt(year));
                stmt.setInt(4, Integer.parseInt(month));
                stmt.setInt(5, Integer.parseInt(day));
                stmt.setString(6, gribFile);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        double maxTemperature = rs.getDouble("max_temperature");
                        response.getWriter().write(String.format("Maximum Temperature: %.2f", maxTemperature));
                    } else {
                        response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given parameters.");
                    }
                }
            }
        } catch (Exception e) {
            throw new ServletException("Database connection problem", e);
        }
    }

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("JDBC Driver not found", e);
        }
    }
}


Make sure to replace `your_database_name`, `your_username`, and `your_password` with your actual database credentials. Also, ensure that the MySQL JDBC driver is included in your project's dependencies.