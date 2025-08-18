import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleWebApp {

    private static final String SERVER_NAME = "MyWebServer";
    private static final String DB_NAME = "myDatabase";
    private static final String DB_USER = "dbUser";
    private static final String DB_PASSWORD = "dbPassword";

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/connection", new ConnectionHandler());
        server.createContext("/server-name", new ServerNameHandler());
        server.createContext("/database-name", new DatabaseNameHandler());
        server.createContext("/database-user", new DatabaseUserHandler());
        server.createContext("/database-password", new DatabasePasswordHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class ConnectionHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "Database connection: " + getDatabaseConnection().toString();
            sendResponse(exchange, response);
        }
    }

    static class ServerNameHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "Server Name: " + SERVER_NAME;
            sendResponse(exchange, response);
        }
    }

    static class DatabaseNameHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "Database Name: " + DB_NAME;
            sendResponse(exchange, response);
        }
    }

    static class DatabaseUserHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "Database User: " + DB_USER;
            sendResponse(exchange, response);
        }
    }

    static class DatabasePasswordHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "Database Password: " + DB_PASSWORD;
            sendResponse(exchange, response);
        }
    }

    private static Connection getDatabaseConnection() {
        try {
            return DriverManager.getConnection("jdbc:h2:~/test", "sa", "");
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

    private static void sendResponse(HttpExchange exchange, String response) throws IOException {
        exchange.sendResponseHeaders(200, response.getBytes().length);
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
}