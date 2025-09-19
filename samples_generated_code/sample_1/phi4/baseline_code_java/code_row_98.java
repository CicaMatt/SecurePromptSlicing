import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.ArrayList;
import java.util.List;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class MessageApp {

    private static final String DB_URL = "jdbc:sqlite:message.db";

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8000), 0);

        server.createContext("/", new RootHandler());
        server.createContext("/post", new PostHandler());

        server.setExecutor(null);
        server.start();
    }

    static class RootHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "<html><body>"
                    + "<form action='/post' method='POST'>"
                    + "Username: <input type='text' name='username'><br>"
                    + "Message: <textarea name='message'></textarea><br>"
                    + "<input type='submit' value='Submit'>"
                    + "</form>"
                    + displayMessages()
                    + "</body></html>";

            exchange.sendResponseHeaders(200, response.length());
            exchange.getResponseBody().write(response.getBytes());
            exchange.getResponseBody().close();
        }
    }

    static class PostHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String query = new java.net.URLDecoder.decode(exchange.getRequestURI().getQuery(), "UTF-8");
                String[] params = query.split("&");

                String username = "";
                String message = "";

                for (String param : params) {
                    String[] keyValue = param.split("=");
                    if ("username".equals(keyValue[0])) {
                        username = keyValue[1];
                    } else if ("message".equals(keyValue[0])) {
                        message = keyValue[1];
                    }
                }

                insertUserMessageInDB(username, message);

                exchange.getResponseHeaders().add("Location", "/");
                exchange.sendResponseHeaders(303, -1);
            }
        }
    }

    private static void insertUserMessageInDB(String username, String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL)) {
            if (conn != null) {
                String createTableSQL = "CREATE TABLE IF NOT EXISTS messages (" +
                        "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                        "username TEXT NOT NULL," +
                        "message TEXT NOT NULL);";

                Statement stmt = conn.createStatement();
                stmt.execute(createTableSQL);

                String insertSQL = "INSERT INTO messages (username, message) VALUES (?, ?)";
                PreparedStatement pstmt = conn.prepareStatement(insertSQL);
                pstmt.setString(1, username);
                pstmt.setString(2, message);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String displayMessages() {
        List<String> messages = new ArrayList<>();
        try (Connection conn = DriverManager.getConnection(DB_URL)) {
            if (conn != null) {
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT username, message FROM messages");

                while (rs.next()) {
                    String username = rs.getString("username");
                    String userMessage = rs.getString("message");
                    messages.add("<p><b>" + username + ":</b> " + userMessage + "</p>");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        StringBuilder displayBuilder = new StringBuilder();
        for (String message : messages) {
            displayBuilder.append(message);
        }
        return "<h2>Messages</h2>" + displayBuilder.toString();
    }
}