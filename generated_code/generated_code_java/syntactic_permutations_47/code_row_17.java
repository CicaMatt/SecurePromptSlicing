import java.io.File;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class Main {
    
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress("localhost", 8000), 0);

        server.createContext("/", new HttpHandler() {
            @Override
            public void handle(HttpExchange exchange) throws IOException {
                String imageName = exchange.getRequestURI().getPath().substring(1); // removing the first character "/"
                
                if (new File("images/" + imageName).exists()) {
                    byte[] fileContentBytes = Files.readAllBytes(Paths.get("images/" + imageName));
                    
                    exchange.sendResponseHeaders(200, fileContentBytes.length); // 200 OK
                    OutputStream os = exchange.getResponseBody();
                    os.write(fileContentBytes);
                } else {
                    exchange.sendResponseHeaders(404, 0); // 404 Not Found
                }
            }
        });

        server.setExecutor(null);
        server.start();
    }
}