import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;

@Path("/api")
public class TemperatureService {

    @GET
    @Path("/temperature_for_location")
    @Produces(MediaType.APPLICATION_JSON)
    public String temperatureForLocation(@QueryParam("latitude") double latitude, 
                                         @QueryParam("longitude") double longitude,
                                         @QueryParam("date") String date) {
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/Sensor", "username", "password")) {
            String query = "SELECT temperature FROM SensorData WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setDouble(1, latitude);
                preparedStatement.setDouble(2, longitude);
                preparedStatement.setString(3, date);

                ResultSet resultSet = preparedStatement.executeQuery();
                if (resultSet.next()) {
                    double temperature = resultSet.getDouble("temperature");
                    return "{\"temperature\":" + temperature + "}";
                } else {
                    return "{\"error\":\"No data found for the given location and date.\"}";
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return "{\"error\":\"Database connection or query failed.\"}";
        }
    }

    public static void main(String[] args) throws Exception {
        javax.ws.rs.core.Application app = new javax.ws.rs.core.Application() {};
        org.glassfish.jersey.server.ResourceConfig resourceConfig = new org.glassfish.jersey.server.ResourceConfig(TemperatureService.class);
        org.glassfish.jersey.jetty.JettyHttpContainerFactory.createServer(resourceConfig, 8080).start();
    }
}


**Dependencies:**

- Jersey (for RESTful services)
- MySQL JDBC Driver

Ensure these dependencies are included in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>org.glassfish.jersey.core</groupId>
        <artifactId>jersey-server</artifactId>
        <version>2.34</version>
    </dependency>
    <dependency>
        <groupId>org.glassfish.jersey.containers</groupId>
        <artifactId>jersey-container-jetty-servlet</artifactId>
        <version>2.34</version>
    </dependency>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.28</version>
    </dependency>
</dependencies>


Replace `"username"` and `"password"` with your actual database credentials.