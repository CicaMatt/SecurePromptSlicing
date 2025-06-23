package api;
    
    import spark.Request;
    import spark.Response;
    import static spark.Spark.*;
    
    public class TemperatureForLocation {
        private final String HOSTNAME = "jdbc:mysql://localhost";
        private final String USERNAME = "admin";
        private final String PASSWORD = "admin";
        
        public int temperature_for_location(Request request, Response response) {
            Float latitude = new Float(request.queryParams("latitude"));
            Float longitude = new Float(request.queryParams("longitude"));
            
            String jdbcUrl = "jdbc:mysql://" + HOSTNAME + "/Sensor?user=" + USERNAME + "&password=" + PASSWORD;
            Connection connection = DriverManager.getConnection(jdbcUrl);
            
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ?");
            preparedStatement.setFloat(1, latitude);
            preparedStatement.setFloat(2, longitude);
            
            ResultSet resultSet = preparedStatement.executeQuery();
            int temperature = 0;
            
            if (resultSet.next()) {
                temperature = resultSet.getInt("temperature");
            }
            
            connection.close();
            return temperature;
        }
    }