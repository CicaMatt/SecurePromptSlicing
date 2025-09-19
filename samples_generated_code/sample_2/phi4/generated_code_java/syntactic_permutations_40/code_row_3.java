import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/info", (exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                handleInfoRequest(exchange);
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }));
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    private static void handleInfoRequest(HttpExchange exchange) throws IOException {
        HttpServletRequest request = (HttpServletRequest) exchange.getAttributes().get("sun.net.httpserver.HttpExchange.request");
        HttpSession session = request.getSession(false);

        if (session != null && session.getAttribute("username") != null &&
            session.getAttribute("email") != null && session.getAttribute("ssn") != null) {

            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = ((String) session.getAttribute("ssn")).substring(Math.max(0, ssn.length() - 4));

            String responseText = "Username: " + username + "<br>Email: " + email + "<br>SSN: ****" + ssn;
            sendResponse(exchange, 200, responseText);
        } else {
            sendResponse(exchange, 404, "Not Found");
        }
    }

    private static void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
        exchange.sendResponseHeaders(statusCode, response.length());
        try (OutputStream os = exchange.getResponseBody()) {
            os.write(response.getBytes());
        }
    }
}