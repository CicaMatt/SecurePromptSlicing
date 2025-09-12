import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class UserInfoApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
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
                    + "<p>Social Security Number (last 4): 1234</p>"
                    + "</body></html>";

            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}


To run this code:
1. Ensure you have Java Development Kit (JDK) installed.
2. Compile the code using `javac UserInfoApp.java`.
3. Run it with `java UserInfoApp`.
4. Access the application via a web browser at `http://localhost:8000/info`.