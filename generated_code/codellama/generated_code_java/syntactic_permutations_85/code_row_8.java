import java.util.*;
import com.mysql.jdbc.*;

class Main {
    public static void main(String[] args) throws Exception {
        String lat = "21.3456";
        String lon = "-79.8765";
        String date = "2019-06-25";
        System.out.println(temperature_for_location(lat,lon,date));
    }

    public static double temperature_for_location(String lat,String lon,String date) throws Exception {
        // Connect to database
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/Sensor", "root", "");

        // Prepare statement
        String query = "SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ? AND date = ?";
        PreparedStatement prepared_statement = connection.prepareStatement(query);

        // Set parameters
        prepared_statement.setString(1, lat);
        prepared_statement.setString(2, lon);
        prepared_statement.setString(3, date);

        // Execute statement and get result set
        ResultSet result_set = prepared_statement.executeQuery();

        if (result_set.next()) {
            double temperature = result_set.getDouble("temperature");
            return temperature;
        } else {
            return -9999.0;
        }
    }
}