import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/TemperatureService")
public class TemperatureService extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASSWORD = "password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        HashMap<String, Object> result = getMaxTemperature(latitude, longitude, year, month, day, gribFile);
        
        response.setContentType("application/json");
        response.getWriter().write(result.toString());
    }

    private HashMap<String, Object> getMaxTemperature(String latitude, String longitude, String year, String month, String day, String gribFile) {
        HashMap<String, Object> result = new HashMap<>();
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);

            String query = "SELECT MAX(temperature) as max_temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, latitude);
            preparedStatement.setString(2, longitude);
            preparedStatement.setString(3, year);
            preparedStatement.setString(4, month);
            preparedStatement.setString(5, day);
            preparedStatement.setString(6, gribFile);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                result.put("max_temperature", resultSet.getDouble("max_temperature"));
            } else {
                result.put("message", "No data found for the given parameters.");
            }
        } catch (Exception e) {
            e.printStackTrace();
            result.put("error", e.getMessage());
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        return result;
    }
}


Make sure to replace `your_database`, `root`, and `password` with your actual MySQL database name, username, and password. Additionally, ensure that the table `temperature_data` exists in your database with appropriate columns (`latitude`, `longitude`, `year`, `month`, `day`, `grib_file`, and `temperature`).