package org.example;
    
    import java.util.*;
    import java.sql.*;
    import com.google.gson.Gson;
    import java.math.BigDecimal;
    import org.json.simple.JSONObject;
    import org.json.simple.parser.JSONParser;
    import spark.template.freemarker.FreeMarkerEngine;
    import spark.ModelAndView;
    
    public class App {
        private static final int PORT = 4567;
        private static final String HOSTNAME = "localhost";
        private static final String DB_NAME = "temperature";
        private static final String USERNAME = "postgres";
        private static final String PASSWORD = "password";
    
        public static void main(String[] args) {
            Gson gson = new Gson();
            JSONParser parser = new JSONParser();
            String locationData;
    
            try (Connection connection = DriverManager.getConnection("jdbc:postgresql://" + HOSTNAME + ":5432/" + DB_NAME, USERNAME, PASSWORD);) {
                Statement statement = connection.createStatement();
                ResultSet resultSet = statement.executeQuery("SELECT * FROM temperature;");
    
                while (resultSet.next()) {
                    locationData = gson.toJson(new LocationTemperature(
                            new BigDecimal(resultSet.getDouble("latitude")),
                            new BigDecimal(resultSet.getDouble("longitude")),
                            resultSet.getString("date"),
                            new BigDecimal(resultSet.getInt("temperature"))));
                }
    
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }

### Response:

    package org.example;
    
    import java.util.*;
    import java.sql.*;
    import com.google.gson.Gson;
    import java.math.BigDecimal;
    import org.json.simple.JSONObject;
    import org.json.simple.parser.JSONParser;
    import spark.template.freemarker.FreeMarkerEngine;
    import spark.ModelAndView;
    
    public class App {
        private static final int PORT = 4567;
        private static final String HOSTNAME = "localhost";
        private static final String DB_NAME = "temperature";
        private static final String USERNAME = "postgres";
        private static final String PASSWORD = "password";
    
        public static void main(String[] args) {
            Gson gson = new Gson();
            JSONParser parser = new JSONParser();
            String locationData;
    
            try (Connection connection = DriverManager.getConnection("jdbc:postgresql://" + HOSTNAME + ":5432/" + DB_NAME, USERNAME, PASSWORD);) {
                Statement statement = connection.createStatement();
                ResultSet resultSet = statement.executeQuery("SELECT * FROM temperature;");
    
                while (resultSet.next()) {
                    locationData = gson.toJson(new LocationTemperature(
                            new BigDecimal(resultSet.getDouble("latitude")),
                            new BigDecimal(resultSet.getDouble("longitude")),
                            resultSet.getString("date"),
                            new BigDecimal(resultSet.getInt("temperature"))));
                }
    
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }