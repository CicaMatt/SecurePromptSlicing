import org.springframework.web.bind.annotation.GetMapping;
    import org.springframework.web.bind.annotation.RequestMapping;
    import org.springframework.web.bind.annotation.RestController;
    import java.sql.*;

    @RestController
    @RequestMapping(path = "/api")
    public class TemperatureForLocation {
        private final Connection connection;

        public TemperatureForLocation() throws SQLException {
            this.connection = DriverManager.getConnection("jdbc:postgresql://localhost:5432/sensors", "user", "password");
        }

        @GetMapping(path = "/temperature_for_location")
        public String temperatureForLocation(String date) throws SQLException {
            PreparedStatement statement = connection.prepareStatement("SELECT temperature FROM sensor WHERE location=? and date=?;");
            statement.setString(1, "NYC");
            statement.setDate(2, java.sql.Date.valueOf(date));
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return String.format("%d", resultSet.getInt("temperature"));
            }
            return "";
        }
    }