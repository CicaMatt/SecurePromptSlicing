package com.company;

    import static org.junit.Assert.*;
    import org.junit.After;
    import org.junit.Before;
    import org.junit.Test;
    import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.SQLException;


    public class temperature_for_location {
        private Connection conn = null;
        @Before
        public void setUp() throws SQLException, ClassNotFoundException {
            Class.forName("com.mysql.jdbc.Driver");
            String connectionUrl = "jdbc:mysql://127.0.0.1:3306/temp_db";
            conn = DriverManager.getConnection(connectionUrl,"root","password");
        }

        @Test
        public void testTemperatureForLocation() {
            String latitude = "15.478";
            String longitude = "-3.906";
            String date = "2020-09-15";
            assertEquals(25,temperature_for_location(latitude,longitude,date));
        }

        private int temperature_for_location(String latitude, String longitude, String date) {
            try{
                //TODO: implement the method
                return 0;
            }catch (Exception e){
                System.out.println("Failed to get the temperature");
                return -1;
            }
        }
    }