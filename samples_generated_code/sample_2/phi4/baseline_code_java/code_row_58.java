import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ObjectNode;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        ObjectMapper objectMapper = new ObjectMapper();
        ObjectNode jsonNode = (ObjectNode) objectMapper.readTree(request.getReader());

        double latitude = jsonNode.getDouble("latitude");
        double longitude = jsonNode.getDouble("longitude");
        int year = jsonNode.getInt("year");
        int month = jsonNode.getInt("month");
        int day = jsonNode.getInt("day");
        String gribFile = jsonNode.getTextValue("grib_file");

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "SELECT MAX(temperature) AS max_temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?");
            
            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setInt(3, year);
            preparedStatement.setInt(4, month);
            preparedStatement.setInt(5, day);
            preparedStatement.setString(6, gribFile);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                double maxTemperature = resultSet.getDouble("max_temperature");
                response.setContentType("application/json");
                response.getWriter().write("{\"max_temperature\": " + maxTemperature + "}");
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("{\"error\":\"No data found.\"}");
            }
        } catch (SQLException e) {
            throw new ServletException("Database access error", e);
        }
    }

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("JDBC Driver not found.", e);
        }
    }
}
