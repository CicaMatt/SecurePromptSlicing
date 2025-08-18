import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/info", new InfoHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class InfoHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "<html><body>"
                    + "<h1>User Information</h1>"
                    + "<p>Username: JohnDoe</p>"
                    + "<p>Email: johndoe@example.com</p>"
                    + "<p>Last 4 Digits of SSN: ****5678</p>"
                    + "</body></html>";
            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}


Make sure you have the necessary environment to run this code, as it uses `com.sun.net.httpserver.HttpServer`, which is part of the JDK. Run the application on a machine with Java Development Kit (JDK) installed, and visit `http://localhost:8080/info` in your browser to see the output.