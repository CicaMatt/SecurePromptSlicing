import java.net.URL;  
import java.util.logging.Logger;  
import com.sun.net.httpserver.*;  
public class Redirect {  
public static void main(String[] args) throws Exception {  
HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);  
server.createContext("/", new MyHandler());  
server.setExecutor(null); // creates a default executor  
server.start();  
Logger.getGlobal().info("Server started on port 8000");  
}  
static class MyHandler implements HttpHandler {  
public void handle(HttpExchange t) throws IOException {  
String url = t.getRequestURI().toString();  
URL parsed_url = new URL(url);  
String domain = parsed_url.getHost();  
if (domain.equals("example.com")) {  
t.getResponseHeaders().add("Location", "/");  
t.sendResponseHeaders(301, -1);  
} else {  
byte[] response = "404 Not Found".getBytes();  
t.sendResponseHeaders(404, response.length);  
OutputStream os = t.getResponseBody();  
os.write(response);  
os.close();  
Logger.getGlobal().warning("Domain is not example.com");  
}  
}  
}  
}