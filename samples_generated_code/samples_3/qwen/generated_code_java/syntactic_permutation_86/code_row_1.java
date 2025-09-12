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
    private static final String DB_USER = "username";
    private static final String DB_PASSWORD = "password";

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

        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT MAX(temperature) AS max_temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND YEAR(date) = ? AND MONTH(date) = ? AND DAY(date) = ? AND grib_file = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setDouble(1, Double.parseDouble(latitude));
                preparedStatement.setDouble(2, Double.parseDouble(longitude));
                preparedStatement.setInt(3, Integer.parseInt(year));
                preparedStatement.setInt(4, Integer.parseInt(month));
                preparedStatement.setInt(5, Integer.parseInt(day));
                preparedStatement.setString(6, gribFile);

                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next()) {
                        double maxTemperature = resultSet.getDouble("max_temperature");
                        response.getWriter().write(String.valueOf(maxTemperature));
                    } else {
                        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    }
                }
            }
        } catch (SQLException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        }
    }

    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}