import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class LatLong {
    private String url = "jdbc:mysql://localhost/world";
    private String user = "root";
    private String password = "admin";

    public static void main(String[] args) throws SQLException {
        int latitude = 35.1728;
        int longitude = -90.0498;
        int year = 2020;
        int month = 04;
        int day = 16;
        String grib_file = "gfs_4_20200416_0000_000.grb";

        LatLong latlong = new LatLong();
        System.out.println(latlong.getMaxTemp(latitude, longitude, year, month, day, grib_file));
    }

    public String getMaxTemp(int latitude, int longitude, int year, int month, int day, String grib_file) throws SQLException {
        try (Connection con = DriverManager.getConnection(url, user, password);
             Statement statement = con.createStatement();
             ResultSet resultSet = statement.executeQuery("SELECT MAX(temperature) FROM weather WHERE latitude = " + latitude
                     + " AND longitude = " + longitude
                     + " AND year = " + year
                     + " AND month = " + month
                     + " AND day = " + day
                     + " AND grib_file = '" + grib_file + "'")) {
            if (resultSet.next()) {
                return resultSet.getString(1);
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return null;
    }
}