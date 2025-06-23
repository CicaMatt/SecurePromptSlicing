import java.sql.*;

public class TemperatureForLocation {
    public static void main(String[] args) throws SQLException {
        Connection connection = DriverManager.getConnection("jdbc:postgresql://localhost:5432/sensor_database",
                "postgres", "admin");
        String latitude = "60";
        String longitude = "18";
        Date date = Date.valueOf("2021-02-19");
        PreparedStatement stmt = connection.prepareStatement(
                "SELECT temperature FROM Sensor WHERE Latitude = ? AND Longitude = ? AND Date = ?");
        stmt.setString(1, latitude);
        stmt.setString(2, longitude);
        stmt.setDate(3, date);
        ResultSet rs = stmt.executeQuery();
        while (rs.next()) {
            System.out.println("The temperature is " + rs.getInt("temperature"));
        }
    }
}