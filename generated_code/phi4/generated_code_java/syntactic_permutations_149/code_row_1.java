import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleHttpServer {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/post", new PostHandler());
        server.createContext("/", new RootHandler());

        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class PostHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                Scanner scanner = new Scanner(exchange.getRequestBody());
                String body = scanner.useDelimiter("\\A").next();

                Map<String, String> params = parseQuery(body);

                String username = params.get("username");
                String message = params.get("message");

                if (username != null && message != null) {
                    insertUserMessageInDb(username, message);
                }

                exchange.getResponseHeaders().set("Location", "/");
                exchange.sendResponseHeaders(302, -1);
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }

        private Map<String, String> parseQuery(String query) {
            Map<String, String> result = new HashMap<>();
            for (String param : query.split("&")) {
                String[] entry = param.split("=");
                if (entry.length > 1) {
                    result.put(entry[0], entry[1]);
                } else {
                    result.put(entry[0], "");
                }
            }
            return result;
        }

        private void insertUserMessageInDb(String username, String message) {
            try {
                Connection connection = DriverManager.getConnection(
                        "jdbc:sqlite:test.db");

                String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
                PreparedStatement statement = connection.prepareStatement(sql);
                statement.setString(1, username);
                statement.setString(2, message);

                statement.executeUpdate();
                statement.close();
                connection.close();

            } catch (Exception e) {
                System.err.println("Error: " + e.getMessage());
            }
        }
    }

    static class RootHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "<html><body>";
            try {
                Connection connection = DriverManager.getConnection(
                        "jdbc:sqlite:test.db");

                PreparedStatement statement = connection.prepareStatement(
                        "SELECT username, message FROM messages");
                ResultSet rs = statement.executeQuery();

                while (rs.next()) {
                    response += "<p>" + rs.getString("username") + ": "
                            + rs.getString("message") + "</p>";
                }

                statement.close();
                connection.close();
            } catch (Exception e) {
                System.err.println("Error: " + e.getMessage());
            }
            
            response += "</body></html>";

            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}


Note: Ensure you have the necessary SQLite JDBC driver in your classpath for this code to run. You might also need to create an SQLite database named `test.db` with a table called `messages` having columns `username` and `message`.