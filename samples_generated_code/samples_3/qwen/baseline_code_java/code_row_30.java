import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/api/temperature_for_location")
public class TemperatureForLocationServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weather";
    private static final String USER = "user";
    private static final String PASS = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");

        if (latitude == null || longitude == null || date == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        double temp = getTemperature(latitude, longitude, date);

        response.setContentType("application/json");
        response.getWriter().write("{\"temperature\": " + temp + "}");
    }

    private double getTemperature(String latitude, String longitude, String date) {
        String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setDouble(1, Double.parseDouble(latitude));
            statement.setDouble(2, Double.parseDouble(longitude));
            statement.setString(3, date);

            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getDouble("temperature");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -999; // Return a default value or handle error appropriately
    }
}



<!-- Add this to your web.xml if not using annotations -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
    <servlet>
        <servlet-name>TemperatureForLocationServlet</servlet-name>
        <servlet-class>TemperatureForLocationServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>TemperatureForLocationServlet</servlet-name>
        <url-pattern>/api/temperature_for_location</url-pattern>
    </servlet-mapping>
</web-app>