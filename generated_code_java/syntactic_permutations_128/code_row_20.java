import java.io.IOException;
import java.io.InputStream;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
public class HttpHelloPage {
    public static void http_hello_page(InputStream request, HttpExchange response) throws IOException {
        String username = request.readLine();
        String greeting = "hello" + username;
        response.sendResponseHeaders(200, greeting.length());
        OutputStream os = response.getResponseBody();
        os.write(greeting.getBytes());
        os.close();
    }
}