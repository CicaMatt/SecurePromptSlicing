import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import org.apache.commons.lang3.StringUtils;
import java.util.*;
public class Server {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress("localhost", 8080), 0);
        server.createContext("/info", new MyHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }
}

class MyHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange exchange) throws IOException {
        String method = exchange.getRequestMethod();
        String response;
        if (method.equalsIgnoreCase("GET")) {
            String queryString = exchange.getRequestURI().getQuery();
            Map<String, String> map = parseQuery(queryString);
            String username = map.get("username");
            String email = map.get("email");
            String ssnum = map.get("ssnum");
            response = "<html><body>" + "<h1>" + "Username: " + username + "</h1>" + "<br>" + "<h1>" + "Email: " + email + "</h1>" + "<br>" + "<h1>" + "Social Security Number: " + StringUtils.leftPad(ssnum, 4) + "</h1>" + "</body></html>";
            exchange.sendResponseHeaders(200, response.length());
        } else {
            response = "Unsupported method";
            exchange.sendResponseHeaders(405, response.length());
        }
        OutputStream os = exchange.getResponseBody();
        os.write(response.toString().getBytes());
    }
}

public static Map<String, String> parseQuery(String queryString) {
    if (queryString == null || queryString.isEmpty()) {
        return Collections.emptyMap();
    }
    Map<String, String> queryParams = new HashMap<>();
    String[] pairs = queryString.split("&");
    for (String pair : pairs) {
        int idx = pair.indexOf("=");
        if (idx != -1 && !pair.startsWith("_")) {
            try {
                queryParams.put(URLDecoder.decode(pair.substring(0, idx), "UTF-8"), URLDecoder.decode(pair.substring(idx + 1), "UTF-8"));
            } catch (UnsupportedEncodingException e) {
            }
        }
    }
    return queryParams;
}