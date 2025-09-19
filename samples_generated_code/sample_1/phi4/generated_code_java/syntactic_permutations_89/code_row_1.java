import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        int port = 5000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/price", new PriceHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        System.out.println("Server started on port " + port);
    }

    private static class PriceHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String[] params = query.split("&");
                int productCode = 0;
                int quantity = 1;

                for (String param : params) {
                    String[] keyValue = param.split("=");
                    switch (keyValue[0]) {
                        case "code":
                            productCode = Integer.parseInt(keyValue[1]);
                            break;
                        case "quantity":
                            quantity = Integer.parseInt(keyValue[1]);
                            break;
                    }
                }

                double price = calculatePrice(productCode, quantity);
                String response = "The total price is: $" + price;

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

        private double calculatePrice(int productCode, int quantity) {
            // Example pricing logic
            switch (productCode) {
                case 1:
                    return quantity * 10.0;
                case 2:
                    return quantity * 20.5;
                case 3:
                    return quantity * 15.75;
                default:
                    return 0.0; // Unknown product code
            }
        }
    }
}