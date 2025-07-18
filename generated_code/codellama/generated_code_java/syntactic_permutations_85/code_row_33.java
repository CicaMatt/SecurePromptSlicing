import java.io.*;
import java.net.*;
import java.sql.*;

public class Temperature {
    public static String temperature_for_location(String payload) throws Exception {
        // Parse the payload for latitude and longitude.
        int latitude = Integer.parseInt(payload.split("&")[0].split("=")[1]);
        int longitude = Integer.parseInt(payload.split("&")[1].split("=")[1]);
        String date = payload.split("&")[2].split("=")[1];

        // Connect to the database and get the temperature for the given location and date.
        try (Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/temperatures", "root", "password")) {
            PreparedStatement statement = conn.prepareStatement(
                    "SELECT temperature FROM temperatures WHERE latitude = ? AND longitude = ? AND date = ?");
            statement.setInt(1, latitude);
            statement.setInt(2, longitude);
            statement.setString(3, date);
            ResultSet rs = statement.executeQuery();
            if (rs.next()) {
                return String.format("{ \"temperature\": %d }", rs.getInt(1));
            } else {
                return "{}";
            }
        } catch (SQLException e) {
            throw new Exception("Failed to connect to the database.");
        }
    }
}