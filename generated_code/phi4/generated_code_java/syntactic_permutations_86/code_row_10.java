import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

@WebServlet("/GetMaxTemperature")
public class GetMaxTemperatureServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabase";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        // Extract parameters from the request
        double latitude = Double.parseDouble(request.getParameter("latitude"));
        double longitude = Double.parseDouble(request.getParameter("longitude"));
        int year = Integer.parseInt(request.getParameter("year"));
        int month = Integer.parseInt(request.getParameter("month"));
        int day = Integer.parseInt(request.getParameter("day"));
        String gribFile = request.getParameter("grib_file");

        // Connect to the database and execute query
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? " +
                         "AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setDouble(1, latitude);
                pstmt.setDouble(2, longitude);
                pstmt.setInt(3, year);
                pstmt.setInt(4, month);
                pstmt.setInt(5, day);
                pstmt.setString(6, gribFile);

                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next()) {
                        double maxTemperature = rs.getDouble(1);
                        response.getWriter().write("Max Temperature: " + maxTemperature);
                    } else {
                        response.getWriter().write("No data found for the given parameters.");
                    }
                }
            }
        } catch (Exception e) {
            throw new ServletException("Database access error", e);
        }
    }
}


**Note**: Ensure that you have a MySQL JDBC driver in your classpath and replace `yourDatabase`, `yourUsername`, and `yourPassword` with actual database credentials. Also, ensure the table name and column names match those used in your database schema.