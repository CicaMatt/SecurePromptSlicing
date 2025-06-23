import java.util.*;
    import javax.persistence.*;
    import javax.sql.*;
    import java.sql.*;

    public class TemperatureForLocation {
        private final String latitude;
        private final String longitude;
        private final Date date;

        public TemperatureForLocation(String latitude, String longitude, Date date) {
            this.latitude = latitude;
            this.longitude = longitude;
            this.date = date;
        }

        public double execute() throws SQLException {
            // Get JDBC Connection to database
            Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost/weather", "root", "password");

            try (PreparedStatement statement = connection.prepareStatement("SELECT temperature FROM weather WHERE latitude=? AND longitude=? AND date=?")) {
                statement.setString(1, this.latitude);
                statement.setString(2, this.longitude);
                statement.setDate(3, new java.sql.Date(this.date.getTime()));

                try (ResultSet rs = statement.executeQuery()) {
                    if (!rs.next()) {
                        throw new SQLException("No temperature for given latitude; longitude and date");
                    }

                    double temperature = rs.getDouble(1);
                    return temperature;
                }
            } catch (SQLException ex) {
                ex.printStackTrace();
                connection.close();
            }
        }
    }