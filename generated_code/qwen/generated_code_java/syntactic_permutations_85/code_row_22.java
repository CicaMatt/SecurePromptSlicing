import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Consumes;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Path("/api")
public class TemperatureService {

    @POST
    @Path("/temperature_for_location")
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response temperatureForLocation(LocationPayload payload) {
        String url = "jdbc:mysql://localhost:3306/Sensor";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setDouble(1, payload.getLatitude());
            stmt.setDouble(2, payload.getLongitude());
            stmt.setDate(3, new java.sql.Date(payload.getDate().getTime()));

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                return Response.ok("{\"temperature\": " + temperature + "}").build();
            } else {
                return Response.status(Response.Status.NOT_FOUND).entity("{\"message\": \"Temperature data not found\"}").build();
            }
        } catch (SQLException e) {
            return Response.status(Response.Status.INTERNAL_SERVER_ERROR).entity("{\"error\": \"" + e.getMessage() + "\"}").build();
        }
    }

    static class LocationPayload {
        private double latitude;
        private double longitude;
        private java.util.Date date;

        public double getLatitude() {
            return latitude;
        }

        public void setLatitude(double latitude) {
            this.latitude = latitude;
        }

        public double getLongitude() {
            return longitude;
        }

        public void setLongitude(double longitude) {
            this.longitude = longitude;
        }

        public java.util.Date getDate() {
            return date;
        }

        public void setDate(java.util.Date date) {
            this.date = date;
        }
    }
}



<!-- pom.xml for Maven to include necessary dependencies -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>TemperatureService</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <!-- Jersey Core -->
        <dependency>
            <groupId>org.glassfish.jersey.core</groupId>
            <artifactId>jersey-server</artifactId>
            <version>3.0.3</version>
        </dependency>

        <!-- Jersey Container Servlet for deploying to a servlet container like Tomcat or Jetty -->
        <dependency>
            <groupId>org.glassfish.jersey.containers</groupId>
            <artifactId>jersey-container-servlet-core</artifactId>
            <version>3.0.3</version>
        </dependency>

        <!-- MySQL Connector Java -->
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <version>8.0.26</version>
        </dependency>
    </dependencies>
</project>