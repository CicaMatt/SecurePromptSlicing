import java.sql.*;

public class Sensor {
    public static void temperature_for_location(String payload) {
        String latitude = parseLatitudeFromPayload(payload);
        String longitude = parseLongitudeFromPayload(payload);
        String date = parseDateFromPayload(payload);

        try (Connection connection = getConnection()) {
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(
                "SELECT temperature FROM readings WHERE latitude='" + latitude + "' AND longitude='" + longitude + "' AND date='" + date + "'");
            if (resultSet.next()) {
                return resultSet.getDouble("temperature");
            } else {
                throw new RuntimeException("No reading found for location and date.");
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}