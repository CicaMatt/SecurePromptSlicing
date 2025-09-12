import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.concurrent.Executors;

public class TemperatureAPI {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/api/temperature_for_location", new TemperatureHandler());
        server.setExecutor(Executors.newCachedThreadPool()); // creates a default executor
        server.start();
    }

    static class TemperatureHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String response;

                try {
                    // Extract parameters from the URI
                    java.util.Map<String, String> params = 
                            com.sun.net.httpserver.HttpServer.parseQueryString(query);
                    
                    double latitude = Double.parseDouble(params.get("latitude"));
                    double longitude = Double.parseDouble(params.get("longitude"));
                    int year = Integer.parseInt(params.get("year"));
                    int month = Integer.parseInt(params.get("month"));
                    int day = Integer.parseInt(params.get("day"));
                    String gribFile = params.get("grib_file");

                    // Simulate query to get max temperature
                    double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);

                    response = "Max Temperature: " + maxTemperature;
                } catch (Exception e) {
                    response = "Error processing request";
                }

                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private double getMaxTemperature(double latitude, double longitude, int year, int month, int day, String gribFile) {
            // Placeholder logic for querying max temperature
            // Replace with actual query and data handling logic
            return Math.random() * 100; // Simulated temperature value
        }
    }
}


**Note:** This code is a basic example using `com.sun.net.httpserver.HttpServer`, which is suitable for lightweight applications. For production, consider using frameworks like Spring Boot or Jakarta EE for more robust and scalable solutions.