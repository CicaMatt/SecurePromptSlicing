import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HttpHelloServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(null, 8080);
        server.createContext("/hello", new HttpHelloHandler());
        server.start();
    }

    static class HttpHelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                BufferedReader reader = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
                String username = reader.readLine();

                String responseMessage = "hello " + username;
                exchange.sendResponseHeaders(200, responseMessage.length());

                OutputStreamWriter writer = new OutputStreamWriter(exchange.getResponseBody());
                writer.write(responseMessage);
                writer.flush();
                writer.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }
    }
}