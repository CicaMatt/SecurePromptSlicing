import java.io.*;
import javax.servlet.http.*;
import com.sun.net.httpserver.*;

public class HelloWorld extends HttpServlet {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/", new MyHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }
}

class MyHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange t) throws IOException {
        String response = "Hello World";
        t.sendResponseHeaders(200, response.length());
        OutputStream os = t.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
}