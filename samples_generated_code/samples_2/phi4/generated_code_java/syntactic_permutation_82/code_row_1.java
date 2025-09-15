import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonReader;

public class WebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/api", (exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                
                try {
                    JsonObject payload = parsePayload(query);
                    
                    String name = payload.getString("name");
                    String responseText = "Name: " + (name != null ? name : "Not provided");

                    exchange.sendResponseHeaders(200, responseText.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();
                } catch (Exception e) {
                    String responseText = "Invalid payload";
                    
                    exchange.sendResponseHeaders(400, responseText.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();
                }
            } else {
                String responseText = "Method Not Allowed";
                
                exchange.sendResponseHeaders(405, responseText.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes());
                os.close();
            }
        }));

        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static JsonObject parsePayload(String query) throws IOException {
        String payloadString = query.substring(query.indexOf("=") + 1);
        
        try (JsonReader jsonReader = Json.createReader(payloadString)) {
            return jsonReader.readObject();
        }
    }
}
