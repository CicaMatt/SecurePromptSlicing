import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HttpHelloServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", new HttpHelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HttpHelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                StringBuilder sb = new StringBuilder();
                BufferedReader br = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
                String line;
                while ((line = br.readLine()) != null) {
                    sb.append(line);
                }
                String username = sb.toString();

                String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";
                exchange.sendResponseHeaders(200, outputbuf.length());
                OutputStream os = exchange.getResponseBody();
                os.write(outputbuf.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
            }
        }
    }
}