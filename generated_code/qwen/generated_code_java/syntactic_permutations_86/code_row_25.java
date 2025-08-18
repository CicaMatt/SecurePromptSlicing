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
    private String jdbcURL = "jdbc:mysql://localhost:3306/weatherdb";
    private String jdbcUsername = "root";
    private String jdbcPassword = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        try (Connection connection = DriverManager.getConnection(jdbcURL, jdbcUsername, jdbcPassword)) {
            String sql = "SELECT MAX(temperature) AS maxTemperature FROM temperatures WHERE latitude = ? AND longitude = ? AND month = ? AND day = ? AND grib_file = ?";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, latitude);
            statement.setString(2, longitude);
            statement.setString(3, month);
            statement.setString(4, day);
            statement.setString(5, gribFile);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                double maxTemperature = resultSet.getDouble("maxTemperature");
                response.setContentType("application/json");
                response.getWriter().write("{\"max_temperature\":" + maxTemperature + "}");
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("{\"error\":\"Data not found\"}");
            }
        } catch (SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("{\"error\":\"Database error\"}");
        }
    }

    @Override
    public void init() throws ServletException {
        super.init();
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException(e);
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