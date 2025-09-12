import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleWebApp {
    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);

        server.createContext("/info", new InfoHandler());

        server.setExecutor(null);
        server.start();
        
        System.out.println("Server is listening on port " + port);
    }

    static class InfoHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "<html><body>"
                    + "<h1>User Information</h1>"
                    + "<p>Username: JohnDoe</p>"
                    + "<p>Email: john.doe@example.com</p>"
                    + "<p>Last 4 Digits of Account Number: ****5678</p>"
                    + "</body></html>";
            
            exchange.sendResponseHeaders(200, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}


To run this code:
1. Ensure Java is installed on your machine.
2. Save the above code in a file named `SimpleWebApp.java`.
3. Compile it using `javac SimpleWebApp.java`.
4. Run it with `java SimpleWebApp`.
5. Visit `http://localhost:8000/info` in a web browser to see the output.