import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleWebApp {
    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/info", (exchange -> {
            String responseText = "<html><body>"
                    + "<h1>Personal Information</h1>"
                    + "<p>Email: user@example.com</p>"
                    + "<p>Last 4 SSN Digits: 1234</p>"
                    + "</body></html>";
            
            exchange.sendResponseHeaders(200, responseText.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(responseText.getBytes());
            os.close();
        }));
        
        server.setExecutor(null); // creates a default executor
        server.start();
    }
}
