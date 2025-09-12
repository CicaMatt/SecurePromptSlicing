import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.HashMap;
import java.util.Map;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class WebApp {

    private static Connection connectToDatabase() throws Exception {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "username";
        String password = "password";

        return DriverManager.getConnection(url, user, password);
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8000), 0);

        server.createContext("/", new RootHandler());
        server.createContext("/post", new PostHandler());

        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class RootHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "<html><body>" +
                    "<form action=\"/post\" method=\"post\">" +
                    "Username: <input type=\"text\" name=\"username\"><br>" +
                    "Message: <textarea name=\"message\"></textarea><br>" +
                    "<input type=\"submit\" value=\"Submit\">" +
                    "</form>" +
                    "<h2>Messages:</h2>";

            try (Connection conn = connectToDatabase()) {
                var stmt = conn.prepareStatement("SELECT username, message FROM messages");
                var rs = stmt.executeQuery();
                
                while (rs.next()) {
                    String username = rs.getString("username");
                    String message = rs.getString("message");

                    response += "<p><strong>" + username + ":</strong> " + message + "</p>";
                }
            } catch (Exception e) {
                e.printStackTrace();
            }

            response += "</body></html>";

            exchange.sendResponseHeaders(200, response.length());
            try (var os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }

    static class PostHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                Map<String, String> params = queryToMap(exchange.getRequestBody().readString());

                String username = params.get("username");
                String message = params.get("message");

                insertUserMessageInDb(username, message);

                exchange.getResponseHeaders().set("Location", "/");
                exchange.sendResponseHeaders(303, -1);
            }
        }

        private void insertUserMessageInDb(String username, String message) {
            try (Connection conn = connectToDatabase()) {
                var stmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
                stmt.setString(1, username);
                stmt.setString(2, message);
                stmt.executeUpdate();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        private Map<String, String> queryToMap(String query) {
            Map<String, String> map = new HashMap<>();
            for (String param : query.split("&")) {
                String[] entry = param.split("=");
                if (entry.length > 1) {
                    map.put(entry[0], java.net.URLDecoder.decode(entry[1], "UTF-8"));
                } else {
                    map.put(entry[0], "");
                }
            }
            return map;
        }
    }

    static class StringReader implements AutoCloseable, java.io.Reader {
        private final String body;

        public StringReader(String string) {
            this.body = string;
        }

        @Override
        public int read(char[] cbuf, int off, int len) throws IOException {
            if (body == null)
                return -1;
            int leftToRead = Math.min(len, body.length() - off);
            body.getChars(0, leftToRead, cbuf, off);
            return leftToRead;
        }

        public String readString() {
            char[] buffer = new char[1024];
            StringBuilder sb = new StringBuilder();
            int n;
            try {
                while ((n = read(buffer, 0, buffer.length)) != -1) {
                    sb.append(buffer, 0, n);
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            return sb.toString();
        }

        @Override
        public void close() throws IOException {
            body = null;
        }
    }
}