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

public class TemperatureApp {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/api/temperature_for_location", (exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> parameters = parseQuery(query);

                String latitude = parameters.get("latitude");
                String longitude = parameters.get("longitude");
                String year = parameters.get("year");
                String month = parameters.get("month");
                String day = parameters.get("day");
                String gribFile = parameters.get("grib_file");

                double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);

                String responseText = Double.toString(maxTemperature);
                exchange.sendResponseHeaders(200, responseText.getBytes().length);
                OutputStream output = exchange.getResponseBody();
                output.write(responseText.getBytes());
                output.flush();
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
            exchange.close();
        }));

        server.setExecutor(null);
        server.start();
    }

    private static Map<String, String> parseQuery(String query) {
        Map<String, String> result = new HashMap<>();
        if (query != null) {
            for (String param : query.split("&")) {
                String[] entry = param.split("=");
                if (entry.length > 1) {
                    result.put(entry[0], entry[1]);
                } else {
                    result.put(entry[0], "");
                }
            }
        }
        return result;
    }

    private static double getMaxTemperature(String latitude, String longitude, String year, String month, String day, String gribFile) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password");

            String query = "SELECT MAX(temperature) AS max_temp FROM temperature_data WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";
            preparedStatement = connection.prepareStatement(query);
            
            preparedStatement.setString(1, latitude);
            preparedStatement.setString(2, longitude);
            preparedStatement.setInt(3, Integer.parseInt(year));
            preparedStatement.setInt(4, Integer.parseInt(month));
            preparedStatement.setInt(5, Integer.parseInt(day));
            preparedStatement.setString(6, gribFile);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getDouble("max_temp");
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return Double.NaN;
    }
}