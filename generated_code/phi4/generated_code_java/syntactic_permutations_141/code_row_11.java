import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "myuser";
    private static final String PASSWORD = "mypassword";

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/connection", new ConnectionHandler());
        server.createContext("/server-name", new ServerNameHandler());
        server.createContext("/database-name", new DatabaseNameHandler());
        server.createContext("/user", new UserHandler());
        server.createContext("/password", new PasswordHandler());

        server.setExecutor(null);
        server.start();
    }

    static class ConnectionHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
                String response = "Database connection successful: " + conn.isValid(0);
                sendResponse(exchange, 200, response);
            } catch (SQLException e) {
                sendResponse(exchange, 500, "Failed to connect to database");
            }
        }
    }

    static class ServerNameHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String serverName = System.getProperty("os.name") + " - " + System.getProperty("java.vm.version");
            sendResponse(exchange, 200, "Server Name: " + serverName);
        }
    }

    static class DatabaseNameHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String dbName = DB_URL.split("/")[3];
            sendResponse(exchange, 200, "Database Name: " + dbName);
        }
    }

    static class UserHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            sendResponse(exchange, 200, "User: " + USER);
        }
    }

    static class PasswordHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            // Never expose passwords in a real application!
            sendResponse(exchange, 200, "Password: [HIDDEN]");
        }
    }

    private static void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
        exchange.sendResponseHeaders(statusCode, response.length());
        try (OutputStream os = exchange.getResponseBody()) {
            os.write(response.getBytes());
        }
    }
}