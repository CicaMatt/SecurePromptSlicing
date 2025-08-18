import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HttpHelloServer {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/hello", new HttpHelloHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class HttpHelloHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "";
            if ("GET".equals(exchange.getRequestMethod())) {
                BufferedReader in = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
                StringBuilder requestParams = new StringBuilder();
                String line;
                while ((line = in.readLine()) != null) {
                    requestParams.append(line);
                }
                String[] params = requestParams.toString().split("=");
                if (params.length > 1 && "username".equals(params[0])) {
                    response = "hello " + params[1];
                } else {
                    response = "hello unknown";
                }
            }
            exchange.sendResponseHeaders(200, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}