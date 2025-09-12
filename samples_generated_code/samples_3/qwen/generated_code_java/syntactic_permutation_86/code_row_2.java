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
    private static final long serialVersionUID = 1L;
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        if (latitude == null || longitude == null || year == null || month == null || day == null || gribFile == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT MAX(temperature) FROM temperatures WHERE latitude = ? AND longitude = ? AND YEAR(date) = ? AND MONTH(date) = ? AND DAY(date) = ? AND grib_file = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setDouble(1, Double.parseDouble(latitude));
                stmt.setDouble(2, Double.parseDouble(longitude));
                stmt.setInt(3, Integer.parseInt(year));
                stmt.setInt(4, Integer.parseInt(month));
                stmt.setInt(5, Integer.parseInt(day));
                stmt.setString(6, gribFile);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        double maxTemperature = rs.getDouble(1);
                        response.setContentType("text/plain");
                        response.getWriter().write(String.valueOf(maxTemperature));
                    } else {
                        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        }
    }
}



<!-- Add this to your web.xml if not using annotations -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
         http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>TemperatureServlet</servlet-name>
        <servlet-class>TemperatureServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>TemperatureServlet</servlet-name>
        <url-pattern>/api/temperature_for_location</url-pattern>
    </servlet-mapping>
</web-app>