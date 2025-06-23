import java.sql.*;
import org.apache.log4j.*;
import java.io.*;
import javax.servlet.http.*;
import com.google.gson.*;

public class TemperatureForLocation extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static Logger logger = Logger.getLogger(TemperatureForLocation.class);
    Gson gson = new Gson();

    // Connect to Sensor database
    public Connection connect(String location) throws ClassNotFoundException, SQLException {
        String databaseUrl = "jdbc:mysql://localhost/sensor";
        Class.forName("com.mysql.cj.jdbc.Driver");
        return DriverManager.getConnection(databaseUrl, "root", "password");
    }

    // Get temperature for given location and date
    public String getTemperatureForLocation(String latitude, String longitude, String date) throws ClassNotFoundException, SQLException {
        Connection connection = connect("sensor");
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("SELECT temperature FROM sensor WHERE location='" + latitude + "," + longitude + "' AND date='" + date + "';");
        String temperature = "";
        if (resultSet.next()) {
            temperature = resultSet.getString(1);
        }
        connection.close();
        return temperature;
    }
    
    @Override
    public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        try {
            JSONObject requestBody = new JSONObject(req.getReader().readLine());
            String latitude = requestBody.getString("latitude");
            String longitude = requestBody.getString("longitude");
            String date = requestBody.getString("date");
            String temperature = getTemperatureForLocation(latitude, longitude, date);
            res.setContentType("application/json");
            PrintWriter out = res.getWriter();
            JSONObject responseJson = new JSONObject();
            responseJson.put("temperature", temperature);
            out.print(responseJson.toString());
        } catch (Exception e) {
            logger.error("Error in TemperatureForLocation servlet: ", e);
            res.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Error occurred while getting temperature for location.");
        }
    }
}

### Explanation:
The code above defines a function called `temperature_for_location()`, which is called when the URL `/api/temperature_for_location` is requested. The function gets the latitude, longitude and date from the payload. It then connects to the database and gets the temperature for the given location and date. Finally, the function returns the temperature as a string.

The code uses the `Gson` library to parse JSON data sent in the request body. The `doPost()` method is used to handle HTTP POST requests, which is the method that will be called when we send a request with the payload to get the temperature for the location. It reads the request body and extracts the latitude, longitude and date from it. Then it calls the `getTemperatureForLocation` function and gets the temperature. The response is then sent back as JSON data using the `PrintWriter` object.