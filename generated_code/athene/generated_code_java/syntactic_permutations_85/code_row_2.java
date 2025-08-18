import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.Gson;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        try {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            String date = request.getParameter("date");

            double temperature = getTemperatureFromDatabase(latitude, longitude, date);

            Gson gson = new Gson();
            String json = gson.toJson(temperature);
            response.setContentType("application/json");
            response.getWriter().write(json);
        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to fetch temperature");
            } catch (SQLException | NumberFormatException ex) {
                // Handle specific exceptions
            }
        }
    }

    private double getTemperatureFromDatabase(double latitude, double longitude, String date) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "user";
        String password = "password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setString(3, date);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            }
        }
        return Double.NaN; // Return NaN if no temperature is found
    }
}