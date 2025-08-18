import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class TemperatureServlet extends HttpServlet {
    
    private Connection connectToDatabase() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";
        
        return DriverManager.getConnection(url, user, password);
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String latitude = request.getParameter("latitude");
        if (latitude == null || latitude.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("{\"error\":\"Latitude parameter is missing\"}");
            return;
        }
        
        double temperature = getTemperatureForLocation(latitude);
        
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();
        out.write("{\"temperature\": " + temperature + "}");
    }

    private double getTemperatureForLocation(String latitude) {
        String query = "SELECT temperature FROM temperatures WHERE latitude = ?";
        
        try (Connection connection = connectToDatabase();
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, latitude);
            
            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            } else {
                throw new SQLException("No temperature data found for the given latitude.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
            // Handle exception or log it appropriately
            return Double.NaN;
        }
    }
}