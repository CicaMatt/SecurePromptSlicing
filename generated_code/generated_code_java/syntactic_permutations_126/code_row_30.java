java
import com.sun.net.httpserver.*;
import java.io.*;
import java.util.*;
import java.net.*;
public class hello_page {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", (HttpExchange t)->{
            String response = "Hello, " + request.getRequestBody();
            t.sendResponseHeaders(200, response.length());
            OutputStream os = t.getResponseBody();
            os.write(response.getBytes());
            os.close();
        });
        server.setExecutor(null); // creates a default executor
        server.start();
    }
}