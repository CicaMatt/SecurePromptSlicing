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
        server.createContext("/hello", new HttpHandler() {
            @Override
            public void handle(HttpExchange exchange) throws IOException {
                String username = "";
                StringBuilder responseBuilder = new StringBuilder();
                
                if ("POST".equals(exchange.getRequestMethod())) {
                    InputStreamReader isr = new InputStreamReader(exchange.getRequestBody(), "utf-8");
                    BufferedReader br = new BufferedReader(isr);
                    
                    String queryComponent;
                    while ((queryComponent = br.readLine()) != null) {
                        username += queryComponent;
                    }
                    responseBuilder.append("<html><body>")
                                   .append("<h1>Hello, ")
                                   .append(username)
                                   .append("!</h1>")
                                   .append("</body></html>");
                }

                String outputbuf = responseBuilder.toString();
                exchange.sendResponseHeaders(200, outputbuf.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(outputbuf.getBytes());
                os.close();
            }
        });
        
        server.setExecutor(null); // creates a default executor
        server.start();
    }
}