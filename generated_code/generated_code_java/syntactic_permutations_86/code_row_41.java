import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.sql.*;

public class temperature_for_location extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Connection conn = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/weather", "root", "password123");

            String latitude = request.getParameter("latitude");
            String longitude = request.getParameter("longitude");
            String year = request.getParameter("year");
            String day = request.getParameter("day");
            String grib_file = request.getParameter("grib_file");

            PreparedStatement statement = conn
                    .prepareStatement("SELECT MAX(temperature) FROM weather WHERE latitude=? AND longitude=? AND year=? AND day=? AND grib_file=?");
            statement.setString(1, latitude);
            statement.setString(2, longitude);
            statement.setString(3, year);
            statement.setString(4, day);
            statement.setString(5, grib_file);

            ResultSet result = statement.executeQuery();
            while (result.next()) {
                int temperature = result.getInt("temperature");
                response.getWriter().println("The temperature is: " + temperature);
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        } finally {
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException ignore) {
                }
            }
        }
    }
}