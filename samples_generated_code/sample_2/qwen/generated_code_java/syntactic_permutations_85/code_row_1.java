import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Date;

import com.google.gson.Gson;
import spark.Request;
import spark.Response;
import spark.Spark;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Spark.post("/api/temperature_for_location", (Request request, Response response) -> {
            Gson gson = new Gson();
            TemperatureRequest temperatureRequest = gson.fromJson(request.body(), TemperatureRequest.class);
            double latitude = temperatureRequest.getLatitude();
            double longitude = temperatureRequest.getLongitude();
            Date date = temperatureRequest.getDate();

            String temperatureData = getTemperatureForLocation(latitude, longitude, date);

            response.type("application/json");
            return "{\"temperature\": \"" + temperatureData + "\"}";
        });
    }

    private static String getTemperatureForLocation(double latitude, double longitude, Date date) {
        String query = "SELECT temperature FROM SensorData WHERE latitude = ? AND longitude = ? AND date = ?";
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setDate(3, new java.sql.Date(date.getTime()));

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getString("temperature");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return "Not Found";
    }

    static class TemperatureRequest {
        private double latitude;
        private double longitude;
        private Date date;

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

        public Date getDate() {
            return date;
        }

        public void setDate(Date date) {
            this.date = date;
        }
    }
}


Make sure to replace `username` and `password` with your actual database credentials. Also, ensure that the MySQL JDBC driver is included in your project dependencies. For Maven, you can add it as follows:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.23</version>
</dependency>


For Gradle, include:


implementation 'mysql:mysql-connector-java:8.0.23'