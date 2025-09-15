import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;

public class Main {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/check_mod", new CheckModHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class CheckModHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            String response;

            if (query != null && query.startsWith("username=")) {
                String usernameParam = query.split("&")[0];
                String passwordParam = query.contains("password=") ? query.split("&")[1] : "";
                String sessionParam = query.contains("session=") ? query.split("&")[2] : "";

                String username = usernameParam.substring(usernameParam.indexOf('=') + 1);
                String password = passwordParam.contains("=") ? passwordParam.substring(passwordParam.indexOf('=') + 1) : "";
                String session = sessionParam.contains("=") ? sessionParam.substring(sessionParam.indexOf('=') + 1) : "";

                boolean isModerator = auth_mod(username, password, session);

                response = "User is moderator: " + isModerator;
            } else {
                response = "Invalid request";
            }

            exchange.sendResponseHeaders(200, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }

    static boolean auth_mod(String username, String password, String session) {
        // Placeholder authentication logic for a moderator
        return "admin".equals(username) && "secret".equals(password) && "session123".equals(session);
    }
}
