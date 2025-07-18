import java.sql.*;
import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/api/temperature_for_location") 
public class TemperatureForLocation extends HttpServlet {  
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Connect to the database
        String connectionURL = "jdbc:mysql://localhost/weather_data";
        Connection connection = null;
        
        try{
            Class.forName("com.mysql.cj.jdbc.Driver"); 
            connection = DriverManager.getConnection(connectionURL, "java", "password");

            // Get request parameters for latitude, longitude, year, month and day
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            int year = Integer.parseInt(request.getParameter("year"));
            int month = Integer.parseInt(request.getParameter("month"));
            int day = Integer.parseInt(request.getParameter("day"));
            String grib_file = request.getParameter("grib_file");

            // Create SQL statement
            String sql = "SELECT MAX(Temperature) as temperature FROM weather_data WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?";
            PreparedStatement statement = connection.prepareStatement(sql); 
            
            // Set the parameters
            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setInt(3, year);
            statement.setInt(4, month);
            statement.setInt(5, day);
            statement.setString(6, grib_file);
            
            // Execute the query
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                double temperature = resultSet.getDouble("temperature"); 
                
                response.setContentType("text/html;charset=UTF-8");
                PrintWriter out = response.getWriter(); 
                out.println(temperature);
            }

        } catch (ClassNotFoundException | SQLException e) {
            System.out.println("Connection Failed! Check output console");
            e.printStackTrace();
            
            return;
        } finally {
            if (connection != null) {
                connection.close();
            }
        }
    }
}