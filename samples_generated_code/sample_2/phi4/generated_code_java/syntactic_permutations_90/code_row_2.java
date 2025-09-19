import java.io.*;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import org.yaml.snakeyaml.Yaml;

public class ProductService {

    public static void main(String[] args) throws IOException {
        int port = 8080;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/calculate_price", new CalculatePriceHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    public static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A":
                return 10.99;
            case "B":
                return 5.49;
            case "C":
                return 7.99;
            default:
                throw new IllegalArgumentException("Invalid product code");
        }
    }

    static class CalculatePriceHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                if (query != null && !query.isEmpty()) {
                    try {
                        Yaml yaml = new Yaml();
                        var data = yaml.load(query);
                        String productCode = (String) ((java.util.Map<?, ?>) data).get("product_code");
                        int quantity = ((Number) ((java.util.Map<?, ?>) data).get("quantity")).intValue();

                        double unitPrice = get_price_for_product_code(productCode);
                        double totalPrice = unitPrice * quantity;

                        String response = new Yaml().dump(java.util.Collections.singletonMap("total_price", totalPrice));
                        exchange.sendResponseHeaders(200, response.getBytes().length);
                        OutputStream os = exchange.getResponseBody();
                        os.write(response.getBytes());
                        os.close();
                    } catch (Exception e) {
                        String response = "400 Bad Request: " + e.getMessage();
                        exchange.sendResponseHeaders(400, response.getBytes().length);
                        OutputStream os = exchange.getResponseBody();
                        os.write(response.getBytes());
                        os.close();
                    }
                } else {
                    String response = "400 Bad Request: Missing query parameter";
                    exchange.sendResponseHeaders(400, response.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                    os.close();
                }
            } else {
                String response = "405 Method Not Allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }
    }
}
