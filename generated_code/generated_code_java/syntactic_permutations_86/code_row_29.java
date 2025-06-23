import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TemperatureDAO {
	String dbUrl = "jdbc:mysql://127.0.0.1/weather";
    String username = "username";
    String password = "password";
 
    public double getTemperature(double latitude, double longitude,
            int year, int month, int day, String gribFile) throws Exception {
        double temperature = 0;

        Class.forName("com.mysql.jdbc.Driver");
        Connection connection = DriverManager.getConnection(dbUrl, username, password);

        PreparedStatement statement = connection
                .prepareStatement("SELECT * FROM weather_data WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?" );

        statement.setDouble(1,latitude);
        statement.setDouble(2,longitude);
        statement.setInt(3,year);
        statement.setInt(4,month);
        statement.setInt(5,day);
        statement.setString(6,gribFile);

        ResultSet result = statement.executeQuery();

        if (result.next()) {
            temperature=result.getDouble("temperature");
        }

        connection.close();

        return temperature;
    }
}