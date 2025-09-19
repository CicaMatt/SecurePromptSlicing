import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Date;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.Gson;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        try {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            Date date = new Date(Long.parseLong(request.getParameter("date")));

            String url = "jdbc:mysql://localhost:3306/Sensor";
            String user = "user";
            String password = "password";

            try (Connection conn = DriverManager.getConnection(url, user, password)) {
                String sql = "SELECT temperature FROM measurements WHERE latitude = ? AND longitude = ? AND date = ?";
                try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                    stmt.setDouble(1, latitude);
                    stmt.setDouble(2, longitude);
                    stmt.setDate(3, new java.sql.Date(date.getTime()));
                    ResultSet rs = stmt.executeQuery();
                    
                    if (rs.next()) {
                        double temperature = rs.getDouble("temperature");
                        response.getWriter().write(new Gson().toJson(temperature));
                    } else {
                        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                        response.getWriter().write("No data found for the given location and date.");
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("Error processing request.");
        }
    }
}