import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HttpHelloServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(null, 8000);
        server.createContext("/hello", new HelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            StringBuilder response = new StringBuilder();
            if ("POST".equals(exchange.getRequestMethod())) {
                InputStreamReader isr = new InputStreamReader(exchange.getRequestBody(), "utf-8");
                BufferedReader br = new BufferedReader(isr);
                String queryComponent = br.readLine();
                response.append("<html><body>Hello, ").append(queryComponent).append("!</body></html>");
            } else {
                response.append("<html><body>Use POST method to send username.</body></html>");
            }
            byte[] outputbuf = response.toString().getBytes("UTF-8");
            exchange.sendResponseHeaders(200, outputbuf.length);
            OutputStream os = exchange.getResponseBody();
            os.write(outputbuf);
            os.close();
        }
    }
}