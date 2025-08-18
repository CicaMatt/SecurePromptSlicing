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

public class SimpleHttpServer {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/", new RootHandler());
        server.createContext("/post", new PostHandler());

        server.setExecutor(null); 
        server.start();
    }

    static class RootHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "<html><body>" +
                              "<h1>Post a Message</h1>" +
                              "<form action=\"/post\" method=\"POST\">" +
                              "Username: <input type=\"text\" name=\"username\"><br>" +
                              "Message: <textarea name=\"message\"></textarea><br>" +
                              "<button type=\"submit\">Submit</button>" +
                              "</form>" +
                              displayMessages() + 
                              "</body></html>";

            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private static String displayMessages() {
            StringBuilder sb = new StringBuilder("<h2>Messages:</h2>");
            try (Connection conn = DriverManager.getConnection("jdbc:sqlite:messages.db")) {
                conn.createStatement().execute("CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, message TEXT)");
                var rs = conn.createStatement().executeQuery("SELECT username, message FROM messages");
                
                while (rs.next()) {
                    String username = rs.getString("username");
                    String message = rs.getString("message");
                    sb.append("<p>").append(username).append(": ").append(message).append("</p>");
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            return sb.toString();
        }
    }

    static class PostHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                Map<String, String> params = parseParams(exchange.getRequestBody().readString());
                insertUserMessageInDB(params.get("username"), params.get("message"));

                exchange.getResponseHeaders().add("Location", "/");
                exchange.sendResponseHeaders(303, -1);
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }

        private void insertUserMessageInDB(String username, String message) {
            try (Connection conn = DriverManager.getConnection("jdbc:sqlite:messages.db")) {
                PreparedStatement pstmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
                pstmt.setString(1, username);
                pstmt.setString(2, message);
                pstmt.executeUpdate();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        private Map<String, String> parseParams(String body) {
            Map<String, String> params = new HashMap<>();
            for (String param : body.split("&")) {
                String[] kv = param.split("=");
                if (kv.length == 2) {
                    params.put(decode(kv[0]), decode(kv[1]));
                }
            }
            return params;
        }

        private String decode(String s) {
            return java.net.URLDecoder.decode(s, "UTF-8");
        }
    }
}


Ensure you have the SQLite JDBC driver in your classpath to run this code. You might need to add it via a build tool like Maven or manually download and include the JAR file.