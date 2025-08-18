import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemperatureServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        try {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            String date = request.getParameter("date");

            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND date = ?";
            
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            ResultSet rs = pstmt.executeQuery();

            double temperature = 0.0;
            if (rs.next()) {
                temperature = rs.getDouble("temperature");
            }

            response.setContentType("application/json");
            response.getWriter().write("{\"temperature\":" + temperature + "}");
            
        } catch (Exception e) {
            e.printStackTrace();
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for deploying as a servlet in a web container like Tomcat.
    }
}


Make sure to replace `your_database_name`, `your_db_username`, and `your_db_password` with your actual database details. Additionally, ensure that the appropriate JDBC driver for MySQL is included in your project dependencies.