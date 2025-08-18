import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleWebApp {

    private static final int PORT = 5000;
    
    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(PORT), 0);
        
        server.createContext("/price", (exchange -> {
            String query = exchange.getRequestURI().getQuery();
            
            if (query != null && query.startsWith("productCode=")) {
                String productCode = query.split("=")[1];
                int quantity = extractQuantity(query, productCode);
                
                double price = calculatePrice(productCode, quantity);
                
                String responseText = "Total Price: $" + price;
                sendResponse(exchange, 200, responseText.getBytes());
            } else {
                sendResponse(exchange, 400, "Invalid request".getBytes());
            }
        }));
        
        server.setExecutor(null); // creates a default executor
        server.start();
    }
    
    private static double calculatePrice(String productCode, int quantity) {
        double basePrice = getProductBasePrice(productCode);
        if (basePrice == -1) {
            return -1;
        }
        return basePrice * quantity;
    }

    private static double getProductBasePrice(String productCode) {
        switch (productCode.toLowerCase()) {
            case "abc123":
                return 10.0;
            case "xyz789":
                return 20.5;
            default:
                return -1; // invalid product code
        }
    }

    private static int extractQuantity(String query, String productCode) {
        if (query.contains("quantity=")) {
            String[] params = query.split("&");
            for (String param : params) {
                if (param.startsWith("quantity=")) {
                    return Integer.parseInt(param.split("=")[1]);
                }
            }
        }
        return 1; // default quantity
    }

    private static void sendResponse(HttpExchange exchange, int statusCode, byte[] response) throws IOException {
        exchange.sendResponseHeaders(statusCode, response.length);
        OutputStream os = exchange.getResponseBody();
        os.write(response);
        os.close();
    }
}