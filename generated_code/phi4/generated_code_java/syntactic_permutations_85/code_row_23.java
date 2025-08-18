import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;

@Path("/api/temperature_for_location")
public class TemperatureService {

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public String temperatureForLocation(@QueryParam("latitude") double latitude,
                                        @QueryParam("longitude") double longitude,
                                        @QueryParam("date") String date) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Establish a database connection
            connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/Sensor", "username", "password");

            String query = "SELECT temperature FROM SensorData WHERE latitude = ? AND longitude = ? AND date = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setString(3, date);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return "{\"temperature\": \"" + resultSet.getDouble("temperature") + "\"}";
            } else {
                return "{\"error\": \"Temperature data not found\"}";
            }

        } catch (Exception e) {
            e.printStackTrace();
            return "{\"error\": \"Database connection error\"}";
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for running the server, 
        // such as initializing and starting a RESTful service
    }
}


Make sure to replace `username` and `password` with your actual database credentials. Additionally, ensure that you have the necessary JDBC driver in your classpath (e.g., MySQL Connector/J for MySQL databases) and configure any server setup required to run this as a RESTful service (using frameworks like Jersey or Spring Boot).