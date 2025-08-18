import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/api/temperature_for_location")
public class TemperatureForLocationServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        if (latitude == null || longitude == null || date == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameters: latitude, longitude, or date");
            return;
        }

        double temp = getTemperature(latitude, longitude, date);
        PrintWriter out = response.getWriter();
        response.setContentType("application/json");
        out.print("{\"temperature\":" + temp + "}");
        out.flush();
    }

    private double getTemperature(String latitude, String longitude, String date) {
        double temperature = -999.0; // Default value indicating an error

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setDouble(1, Double.parseDouble(latitude));
            stmt.setDouble(2, Double.parseDouble(longitude));
            stmt.setString(3, date);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                temperature = rs.getDouble("temperature");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return temperature;
    }
}