import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;

public class TemperatureService {

    private static final String DB_URL = "jdbc:your_database_url";
    private static final String USER = "your_db_user";
    private static final String PASSWORD = "your_db_password";

    public static void main(String[] args) {
        // Example request payload
        String jsonPayload = "{\"latitude\": 40.7128, \"longitude\": -74.0060, \"date\": \"2023-10-01\"}";

        try {
            double temperature = getTemperatureForLocation(jsonPayload);
            System.out.println("Temperature: " + temperature);
        } catch (IOException | DatabaseException e) {
            e.printStackTrace();
        }
    }

    public static double getTemperatureForLocation(String jsonPayload) throws IOException, DatabaseException {
        ObjectMapper objectMapper = new ObjectMapper();
        JsonNode rootNode = objectMapper.readTree(jsonPayload);

        double latitude = rootNode.get("latitude").asDouble();
        double longitude = rootNode.get("longitude").asDouble();
        String date = rootNode.get("date").asText();

        return queryTemperatureFromDatabase(latitude, longitude, date);
    }

    private static double queryTemperatureFromDatabase(double latitude, double longitude, String date) throws DatabaseException {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            String sql = "SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ? AND date = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setDouble(1, latitude);
                statement.setDouble(2, longitude);
                statement.setString(3, date);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        return resultSet.getDouble("temperature");
                    } else {
                        throw new DatabaseException("Temperature data not found for the given location and date.");
                    }
                }
            }
        } catch (IOException e) {
            throw new DatabaseException("Database connection error.", e);
        }
    }

    static class DatabaseException extends Exception {
        public DatabaseException(String message) {
            super(message);
        }

        public DatabaseException(String message, Throwable cause) {
            super(message, cause);
        }
    }
}
