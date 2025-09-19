import com.google.gson.Gson;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class Main {
    public static void main(String[] args) {
        port(4567);
        
        post("/api/temperature_for_location", (request, response) -> {
            TemperatureRequest requestObj = new Gson().fromJson(request.body(), TemperatureRequest.class);
            
            try {
                double temperature = temperatureForLocation(requestObj.getLatitude(), 
                                                            requestObj.getLongitude(), 
                                                            requestObj.getDate());
                return String.valueOf(temperature);
            } catch (Exception e) {
                response.status(500);
                return "Error retrieving temperature: " + e.getMessage();
            }
        });
    }

    public static double temperatureForLocation(double latitude, double longitude, String date)
            throws Exception {
        Connection connection = null;
        PreparedStatement statement = null;
        ResultSet resultSet = null;

        try {
            // Connect to the Sensor database
            connection = DriverManager.getConnection("jdbc:sqlite:sensor.db");

            // Prepare SQL query
            String sql = "SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?";
            statement = connection.prepareStatement(sql);
            
            // Set parameters
            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setString(3, date);

            // Execute query and retrieve result
            resultSet = statement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            } else {
                throw new Exception("Temperature data not found for the provided location and date.");
            }
        } finally {
            if (resultSet != null) {
                resultSet.close();
            }
            if (statement != null) {
                statement.close();
            }
            if (connection != null) {
                connection.close();
            }
        }
    }

    static class TemperatureRequest {
        private double latitude;
        private double longitude;
        private String date;

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

        public String getDate() {
            return date;
        }

        public void setDate(String date) {
            this.date = date;
        }
    }
}