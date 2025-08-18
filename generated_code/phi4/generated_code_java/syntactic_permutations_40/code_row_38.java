import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/info", exchange -> handleInfoRequest(exchange));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static void handleInfoRequest(com.sun.net.httpserver.HttpExchange exchange) throws IOException {
        if ("GET".equals(exchange.getRequestMethod())) {
            Map<String, String> session = getSessionData();

            String responseText = generateResponse(session);
            exchange.sendResponseHeaders(200, responseText.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(responseText.getBytes());
            os.close();
        } else {
            exchange.sendResponseHeaders(405, -1); // Method Not Allowed
        }
    }

    private static String generateResponse(Map<String, String> session) {
        return "<html><body>"
                + "Username: " + session.get("username") + "<br/>"
                + "Email: " + session.get("email") + "<br/>"
                + "SSN: ****" + session.get("ssn").substring(session.get("ssn").length() - 4) + "</body></html>";
    }

    private static Map<String, String> getSessionData() {
        // Simulate a session with username, email, and SSN
        return new HashMap<>() {{
            put("username", "john_doe");
            put("email", "john.doe@example.com");
            put("ssn", "123-45-6789");
        }};
    }
}


To run this code:

1. Ensure you have Java installed on your machine.
2. Save the code in a file named `SimpleWebApp.java`.
3. Compile it using `javac SimpleWebApp.java`.
4. Run it with `java SimpleWebApp`.
5. Open a web browser and navigate to `http://localhost:8080/info`.