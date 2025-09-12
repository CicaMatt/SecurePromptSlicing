import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;
import org.json.JSONObject;

public class TemperatureService {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/api/temperature_for_location", (exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> queryParams = parseQuery(query);

                String latitude = queryParams.get("latitude");
                String longitude = queryParams.get("longitude");
                String year = queryParams.get("year");
                String month = queryParams.get("month");
                String day = queryParams.get("day");
                String gribFile = queryParams.get("grib_file");

                if (latitude != null && longitude != null && year != null && month != null && day != null && gribFile != null) {
                    try {
                        double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);
                        JSONObject jsonResponse = new JSONObject();
                        jsonResponse.put("max_temperature", maxTemperature);

                        exchange.sendResponseHeaders(200, jsonResponse.toString().getBytes().length);
                        OutputStream os = exchange.getResponseBody();
                        os.write(jsonResponse.toString().getBytes());
                        os.close();
                    } catch (Exception e) {
                        String response = "Internal Server Error";
                        exchange.sendResponseHeaders(500, response.getBytes().length);
                        OutputStream os = exchange.getResponseBody();
                        os.write(response.getBytes());
                        os.close();
                    }
                } else {
                    String response = "Bad Request: Missing parameters";
                    exchange.sendResponseHeaders(400, response.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }));

        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static Map<String, String> parseQuery(String query) {
        Map<String, String> queryParams = new HashMap<>();
        if (query != null) {
            for (String param : query.split("&")) {
                String[] pair = param.split("=");
                if (pair.length == 2) {
                    queryParams.put(pair[0], pair[1]);
                }
            }
        }
        return queryParams;
    }

    private static double getMaxTemperature(String latitude, String longitude, String year, String month, String day, String gribFile) throws Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Database credentials and URL
            String url = "jdbc:mysql://localhost:3306/temperature_db";
            String user = "root";  // Replace with your username
            String password = "";  // Replace with your password

            connection = DriverManager.getConnection(url, user, password);

            String query = "SELECT MAX(temperature) AS max_temperature FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, latitude);
            preparedStatement.setString(2, longitude);
            preparedStatement.setInt(3, Integer.parseInt(year));
            preparedStatement.setInt(4, Integer.parseInt(month));
            preparedStatement.setInt(5, Integer.parseInt(day));
            preparedStatement.setString(6, gribFile);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getDouble("max_temperature");
            } else {
                throw new Exception("No data found for the given parameters.");
            }
        } finally {
            if (resultSet != null) resultSet.close();
            if (preparedStatement != null) preparedStatement.close();
            if (connection != null) connection.close();
        }
    }
}


**Note:** Replace `root` and the empty password in the JDBC connection string with your actual MySQL username and password. Ensure that the database and table names match those in your setup, and ensure the JSON library is included in your project dependencies.