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

@WebServlet("/MaxTemperatureServlet")
public class MaxTemperatureServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        if (latitude != null && longitude != null && year != null && month != null && day != null && gribFile != null) {
            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                String sql = "SELECT MAX(temperature) AS max_temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                
                PreparedStatement pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, latitude);
                pstmt.setString(2, longitude);
                pstmt.setString(3, year);
                pstmt.setString(4, month);
                pstmt.setString(5, day);
                pstmt.setString(6, gribFile);

                ResultSet rs = pstmt.executeQuery();

                if (rs.next()) {
                    double maxTemperature = rs.getDouble("max_temperature");
                    response.getWriter().write("Maximum Temperature: " + maxTemperature);
                } else {
                    response.getWriter().write("No data found for the provided parameters.");
                }
            } catch (Exception e) {
                throw new ServletException("Database connection problem.", e);
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing required parameters.");
        }
    }

    @Override
    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("MySQL JDBC Driver not found.", e);
        }
    }
}