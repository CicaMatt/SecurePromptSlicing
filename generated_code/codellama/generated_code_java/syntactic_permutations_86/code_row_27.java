package com.example.temperature.api;
    
    import java.sql.Connection;
    import java.sql.PreparedStatement;
    import java.sql.ResultSet;
    
    import javax.ws.rs.*;
    import javax.ws.rs.core.MediaType;
    
    @Path("/temperature_for_location")
    public class TemperatureForLocationResource {
        private static final String QUERY = "SELECT MAX(temp) FROM temperatures WHERE lat = ? AND lon = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
    
        @GET
        @Produces(MediaType.TEXT_PLAIN)
        public double getTemperature(@QueryParam("lat") double latitude, @QueryParam("lon") double longitude, @QueryParam("year") int year, 
                                      @QueryParam("month") int month, @QueryParam("day") int day) {
            Connection connection = null;
            PreparedStatement preparedStatement = null;
            ResultSet resultSet = null;
            try {
                connection = getConnection();
                preparedStatement = connection.prepareStatement(QUERY);
                preparedStatement.setDouble(1, latitude);
                preparedStatement.setDouble(2, longitude);
                preparedStatement.setInt(3, year);
                preparedStatement.setInt(4, month);
                preparedStatement.setInt(5, day);
                resultSet = preparedStatement.executeQuery();
                if (resultSet.next()) {
                    return resultSet.getDouble(1);
                } else {
                    throw new IllegalArgumentException("No matching record found");
                }
            } catch (Exception e) {
                // Log exception and rethrow it as a runtime exception
            } finally {
                closeResources(connection, preparedStatement, resultSet);
            }
        }
    
        private void closeResources(Connection connection, PreparedStatement preparedStatement, ResultSet resultSet) {
            try {
                if (resultSet != null) {
                    resultSet.close();
                }
                if (preparedStatement != null) {
                    preparedStatement.close();
                }
                if (connection != null) {
                    connection.close();
                }
            } catch (Exception e) {
                // Log exception and rethrow it as a runtime exception
            }
        }
    
        private Connection getConnection() throws Exception {
            return null;
        }
    }

