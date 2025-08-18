import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    private static Map<String, Double> productPrices = new HashMap<>();

    static {
        // Example product codes and their prices
        productPrices.put("P001", 10.0);
        productPrices.put("P002", 20.0);
        productPrices.put("P003", 30.0);
    }

    public static double getPriceForProduct(String code) {
        return productPrices.getOrDefault(code, -1.0);
    }

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);

        server.createContext("/calculate", (exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                Map<String, String> params = new HashMap<>();
                for (String param : query.split("&")) {
                    String[] keyValue = param.split("=");
                    params.put(keyValue[0], keyValue.length > 1 ? keyValue[1] : "");
                }

                String code = params.getOrDefault("code", "");
                String quantityStr = params.getOrDefault("quantity", "1");
                int quantity;

                try {
                    quantity = Integer.parseInt(quantityStr);
                } catch (NumberFormatException e) {
                    exchange.sendResponseHeaders(400, 0); // Bad Request
                    return;
                }

                double price = getPriceForProduct(code);

                if (price == -1.0) {
                    String response = "Product not found";
                    exchange.sendResponseHeaders(404, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                } else {
                    double totalCost = price * quantity;
                    String response = String.format("Total cost for %d units of product %s: %.2f", quantity, code, totalCost);
                    exchange.sendResponseHeaders(200, response.length());
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                exchange.sendResponseHeaders(405, 0); // Method Not Allowed
            }
        }));

        server.setExecutor(null); // creates a default executor
        server.start();
    }
}


This Java code sets up a simple web application using `com.sun.net.httpserver.HttpServer`. It defines a function to get the price for a product code and a route `/calculate` that calculates the total cost based on the product code and quantity provided as query parameters. The server listens on port 5000.