import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class TemperatureService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root"; // Change to your database user
    private static final String PASS = "";     // Change to your database password

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter latitude:");
        double latitude = Double.parseDouble(scanner.nextLine());
        System.out.println("Enter longitude:");
        double longitude = Double.parseDouble(scanner.nextLine());
        System.out.println("Enter date (YYYY-MM-DD):");
        String date = scanner.nextLine();

        try {
            double temperature = temperatureForLocation(latitude, longitude, date);
            System.out.println("Temperature: " + temperature + "°C");
        } catch (Exception e) {
            System.err.println("Error retrieving temperature: " + e.getMessage());
        }
    }

    public static double temperatureForLocation(double latitude, double longitude, String date) throws Exception {
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
                throw new Exception("Temperature data not found for the given location and date.");
            }
        } finally {
            if (rs != null) rs.close();
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }
}