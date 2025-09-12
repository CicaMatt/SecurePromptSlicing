import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Spark;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "yourDatabaseUser";
    private static final String PASS = "yourDatabasePassword";

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.post("/api/temperature_for_location", TemperatureService::temperatureForLocation);
    }

    public static Object temperatureForLocation(Request request, Response response) {
        try {
            double latitude = Double.parseDouble(request.queryParams("latitude"));
            double longitude = Double.parseDouble(request.queryParams("longitude"));
            String date = request.queryParams("date");

            return getTemperatureFromDatabase(latitude, longitude, date);
        } catch (Exception e) {
            response.status(400);
            return "Error processing request: " + e.getMessage();
        }
    }

    private static double getTemperatureFromDatabase(double latitude, double longitude, String date) throws SQLException {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT temperature FROM TemperatureData WHERE latitude = ? AND longitude = ? AND date = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setDouble(1, latitude);
            pstmt.setDouble(2, longitude);
            pstmt.setString(3, date);

            rs = pstmt.executeQuery();
            
            if (rs.next()) {
                return rs.getDouble("temperature");
            } else {
                throw new SQLException("No temperature data found for the given parameters.");
            }
        } finally {
            if (rs != null) rs.close();
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }
}


**Dependencies:**

1. JDBC Driver for MySQL
2. Spark Java Framework

To run the code, include these dependencies in your `build.gradle`:


dependencies {
    implementation 'com.sparkjava:spark-core:2.9.3'
    implementation 'mysql:mysql-connector-java:8.0.29'
}


Or in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.29</version>
    </dependency>
</dependencies>