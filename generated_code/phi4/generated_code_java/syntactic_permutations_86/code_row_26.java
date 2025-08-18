import java.io.IOException;
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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabaseName";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        if (latitude == null || longitude == null || year == null || day == null || gribFile == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT MAX(temperature) AS max_temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND day = ? AND grib_file = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, latitude);
                pstmt.setString(2, longitude);
                pstmt.setString(3, year);
                pstmt.setString(4, day);
                pstmt.setString(5, gribFile);

                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next()) {
                        double maxTemperature = rs.getDouble("max_temperature");
                        response.setContentType("application/json");
                        response.getWriter().write("{\"max_temperature\":" + maxTemperature + "}");
                    } else {
                        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    }
                }
            }
        } catch (SQLException e) {
            throw new ServletException("Database access error", e);
        }
    }

    public static void main(String[] args) throws Exception {
        // This is just for standalone testing; remove or replace with a proper server setup in production.
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        server.setHandler(new org.eclipse.jetty.servlet.ServletContextHandler() {{
            ServletHolder holder = new ServletHolder("TemperatureServlet", TemperatureServlet.class);
            addServlet(holder, "/api/temperature_for_location");
        }});
        server.start();
        server.join();
    }
}


**Note:** Replace `yourDatabaseName`, `yourUsername`, and `yourPassword` with your actual MySQL database name, username, and password. This code requires a MySQL JDBC driver to be included in the classpath and uses Jetty as an embedded server for demonstration purposes. Adjust the server setup according to your production environment needs.