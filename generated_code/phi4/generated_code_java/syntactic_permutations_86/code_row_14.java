import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.google.gson.JsonObject;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        JsonObject jsonResponse = getMaxTemperature(latitude, longitude, year, month, day, gribFile);

        response.setContentType("application/json");
        response.getWriter().write(jsonResponse.toString());
    }

    private JsonObject getMaxTemperature(String latitude, String longitude, String year,
                                         String month, String day, String gribFile) {
        JsonObject result = new JsonObject();
        String url = "jdbc:mysql://localhost:3306/temperature_db";
        String user = "root";
        String password = "password";

        String query = "SELECT MAX(temperature) AS max_temp FROM temperature_data WHERE latitude = ? AND longitude = ? "
                + "AND year = ? AND month = ? AND day = ? AND grib_file = ?";
        
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            
            preparedStatement.setString(1, latitude);
            preparedStatement.setString(2, longitude);
            preparedStatement.setInt(3, Integer.parseInt(year));
            preparedStatement.setInt(4, Integer.parseInt(month));
            preparedStatement.setInt(5, Integer.parseInt(day));
            preparedStatement.setString(6, gribFile);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    double maxTemp = resultSet.getDouble("max_temp");
                    result.addProperty("max_temperature", maxTemp);
                } else {
                    result.addProperty("error", "No data found for the given parameters.");
                }
            }

        } catch (SQLException e) {
            result.addProperty("error", "Database connection failed: " + e.getMessage());
        }

        return result;
    }
}