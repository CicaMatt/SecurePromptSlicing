import org.yaml.snakeyaml.DumperOptions;
import org.yaml.snakeyaml.Yaml;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class ProductService {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        // Initialize with some products and their prices
        productPrices.put("P001", 19.99);
        productPrices.put("P002", 29.99);
        productPrices.put("P003", 9.99);
    }

    public static double getPriceForProductCode(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    private static class CalculatePriceHandler extends com.sun.net.httpserver.HttpHandler {

        @Override
        public void handle(com.sun.net.httpserver.HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            if (query == null || !query.startsWith("payload=")) {
                sendResponse(exchange, 400, "Invalid request");
                return;
            }

            String yamlPayload = query.substring(8);
            Yaml yaml = new Yaml();
            Map<String, Object> payloadMap = yaml.load(yamlPayload);

            if (payloadMap == null || !payloadMap.containsKey("product_code") || !payloadMap.containsKey("quantity")) {
                sendResponse(exchange, 400, "Invalid payload");
                return;
            }

            String productCode = (String) payloadMap.get("product_code");
            double quantity = ((Number) payloadMap.get("quantity")).doubleValue();

            double pricePerItem = getPriceForProductCode(productCode);
            double totalPrice = pricePerItem * quantity;

            Map<String, Double> result = new HashMap<>();
            result.put("total_price", totalPrice);

            DumperOptions options = new DumperOptions();
            options.setDefaultFlowStyle(DumperOptions.FlowStyle.BLOCK);
            Yaml yamlOutput = new Yaml(options);
            String responsePayload = yamlOutput.dump(result);

            sendResponse(exchange, 200, responsePayload);
        }

        private void sendResponse(com.sun.net.httpserver.HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.getBytes().length);
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/calculate_price", new CalculatePriceHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port 8000");
    }
}
