import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/weatherdb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            int year = Integer.parseInt(request.getParameter("year"));
            int month = Integer.parseInt(request.getParameter("month"));
            int day = Integer.parseInt(request.getParameter("day"));
            String gribFile = request.getParameter("grib_file");

            String query = "SELECT MAX(temperature) FROM temperature_data WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setDouble(1, latitude);
                preparedStatement.setDouble(2, longitude);
                preparedStatement.setInt(3, year);
                preparedStatement.setInt(4, month);
                preparedStatement.setInt(5, day);
                preparedStatement.setString(6, gribFile);

                ResultSet resultSet = preparedStatement.executeQuery();
                if (resultSet.next()) {
                    double maxTemperature = resultSet.getDouble(1);
                    response.getWriter().write(String.valueOf(maxTemperature));
                } else {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "No temperature data found");
                }
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, e.getMessage());
        }
    }
}