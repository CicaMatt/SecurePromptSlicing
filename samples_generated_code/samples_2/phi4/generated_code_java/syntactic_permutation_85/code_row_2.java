import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root"; // replace with your database username
    private static final String PASS = ""; // replace with your database password

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        StringBuilder payload = new StringBuilder();
        BufferedReader reader = request.getReader();
        String line;
        while ((line = reader.readLine()) != null) {
            payload.append(line);
        }

        // Parse the latitude, longitude and date from JSON
        double latitude = Double.parseDouble(payload.substring(payload.indexOf("\"latitude\":") + 12, payload.indexOf(",", payload.indexOf("\"latitude\""))));
        double longitude = Double.parseDouble(payload.substring(payload.indexOf("\"longitude\":") + 13, payload.indexOf("}", payload.indexOf("\"longitude\""))).trim());
        String date = payload.substring(payload.indexOf("\"date\":") + 8, payload.indexOf("}", payload.indexOf("\"date\"")));

        // Get temperature from database
        float temperature = getTemperatureFromDatabase(latitude, longitude, date);

        response.setContentType("application/json");
        response.getWriter().write("{\"temperature\":" + temperature + "}");
    }

    private float getTemperatureFromDatabase(double latitude, double longitude, String date) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            // Load the MySQL JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish a connection to the database
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Create a SQL query to get temperature for given latitude, longitude and date
            String sql = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND reading_date = ?";
            
            pstmt = conn.prepareStatement(sql);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            // Execute the query and get the result
            rs = pstmt.executeQuery();

            if (rs.next()) {
                return rs.getFloat("temperature");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        return Float.NaN; // Return NaN if temperature is not found
    }
}