import com.fasterxml.jackson.databind.ObjectMapper;
import io.javalin.Javalin;
import io.javalin.http.Context;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TemperatureApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.addStaticFiles("/public");
        }).start(7000);

        app.post("/api/temperature_for_location", TemperatureApp::handleTemperatureRequest);
    }

    private static void handleTemperatureRequest(Context ctx) {
        ObjectMapper objectMapper = new ObjectMapper();
        
        try {
            RequestData requestData = objectMapper.readValue(ctx.body(), RequestData.class);

            double maxTemperature = getMaxTemperature(
                requestData.getLatitude(),
                requestData.getLongitude(),
                requestData.getYear(),
                requestData.getMonth(),
                requestData.getDay(),
                requestData.getGribFile()
            );

            ctx.result(String.valueOf(maxTemperature));

        } catch (Exception e) {
            ctx.status(500).result("Internal Server Error: " + e.getMessage());
        }
    }

    private static double getMaxTemperature(double latitude, double longitude, int year, int month, int day, String gribFile) throws SQLException {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");

            String query = "SELECT MAX(temperature) FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setDouble(1, latitude);
            preparedStatement.setDouble(2, longitude);
            preparedStatement.setInt(3, year);
            preparedStatement.setInt(4, month);
            preparedStatement.setInt(5, day);
            preparedStatement.setString(6, gribFile);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getDouble(1);
            }

        } finally {
            if (resultSet != null) {
                resultSet.close();
            }
            if (preparedStatement != null) {
                preparedStatement.close();
            }
            if (connection != null) {
                connection.close();
            }
        }

        throw new SQLException("Failed to retrieve temperature data.");
    }

    static class RequestData {
        private double latitude;
        private double longitude;
        private int year;
        private int month;
        private int day;
        private String gribFile;

        // Getters and setters
        public double getLatitude() { return latitude; }
        public void setLatitude(double latitude) { this.latitude = latitude; }

        public double getLongitude() { return longitude; }
        public void setLongitude(double longitude) { this.longitude = longitude; }

        public int getYear() { return year; }
        public void setYear(int year) { this.year = year; }

        public int getMonth() { return month; }
        public void setMonth(int month) { this.month = month; }

        public int getDay() { return day; }
        public void setDay(int day) { this.day = day; }

        public String getGribFile() { return gribFile; }
        public void setGribFile(String gribFile) { this.gribFile = gribFile; }
    }
}