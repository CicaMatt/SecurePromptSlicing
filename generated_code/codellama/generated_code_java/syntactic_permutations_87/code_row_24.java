package io.kenxue.api.temperature;
    
    import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.ResultSet;
    import java.sql.Statement;
    
    public class TemperatureForLocation {
        private static final String CONNECTION_URL = "jdbc:mysql://localhost/temperature";
        private static final String USERNAME = "root";
        private static final String PASSWORD = "";
        private static final String QUERY = "SELECT * FROM temperature WHERE latitude = ? AND longitude = ? AND date = ?";
    
        public String temperatureForLocation(double latitude, double longitude, String date) {
            Connection connection = null;
            Statement statement = null;
            ResultSet resultSet = null;
            try {
                // Register JDBC driver
                Class.forName("com.mysql.cj.jdbc.Driver");
    
                // Open a connection
                connection = DriverManager.getConnection(CONNECTION_URL, USERNAME, PASSWORD);
    
                // Execute SQL query
                statement = connection.createStatement();
                resultSet = statement.executeQuery(QUERY);
    
                // Extract temperature from the result
                double temperature = 0;
                while (resultSet.next()) {
                    temperature = resultSet.getDouble("temperature");
                }
    
                return temperature + "";
            } catch (Exception e) {
                System.err.println(e);
                return "Error: " + e;
            } finally {
                if (statement != null) {
                    try {
                        statement.close();
                    } catch (Exception e) {
                        // nothing we can do
                    }
                }
                if (connection != null) {
                    try {
                        connection.close();
                    } catch (Exception e) {
                        // nothing we can do
                    }
                }
            }
        }
    }