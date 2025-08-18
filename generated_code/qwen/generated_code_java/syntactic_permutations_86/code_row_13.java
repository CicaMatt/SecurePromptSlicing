import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/TemperatureQuery")
public class TemperatureQueryServlet extends HttpServlet {
    private static final String JDBC_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String JDBC_USER = "username";
    private static final String JDBC_PASSWORD = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();

        try (Connection connection = DriverManager.getConnection(JDBC_URL, JDBC_USER, JDBC_PASSWORD)) {
            String query = "SELECT MAX(temperature) AS max_temp FROM weather_data WHERE latitude=? AND longitude=? AND YEAR(date)=? AND MONTH(date)=? AND DAY(date)=? AND grib_file=?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setDouble(1, Double.parseDouble(latitude));
                preparedStatement.setDouble(2, Double.parseDouble(longitude));
                preparedStatement.setInt(3, Integer.parseInt(year));
                preparedStatement.setInt(4, Integer.parseInt(month));
                preparedStatement.setInt(5, Integer.parseInt(day));
                preparedStatement.setString(6, gribFile);

                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next()) {
                        double maxTemp = resultSet.getDouble("max_temp");
                        out.println("Maximum Temperature: " + maxTemp);
                    } else {
                        out.println("No data found for the given parameters.");
                    }
                }
            }
        } catch (Exception e) {
            out.println("Error: " + e.getMessage());
        }
    }
}