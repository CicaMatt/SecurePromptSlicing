import java.sql.Connection;
import java.sql.DriverManager;
import java.util.Properties;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "myuser";
    private static final String DB_PASSWORD = "mypassword";
    private static final String SERVER_NAME = "localhost";

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(SERVER_NAME, 8080), 0);
        
        server.createContext("/db-connection", new DbConnectionHandler());
        server.createContext("/server-name", new ServerNameHandler());
        server.createContext("/database-name", new DatabaseNameHandler());
        server.createContext("/database-user", new DatabaseUserHandler());
        server.createContext("/database-password", new DatabasePasswordHandler());

        server.setExecutor(null);
        server.start();
    }

    public static Connection getDatabaseConnection() throws Exception {
        Properties properties = new Properties();
        properties.setProperty("user", DB_USER);
        properties.setProperty("password", DB_PASSWORD);

        return DriverManager.getConnection(DB_URL, properties);
    }

    public static String getServerName() {
        return SERVER_NAME;
    }

    public static String getDatabaseName() {
        return "mydatabase";
    }

    public static String getDatabaseUser() {
        return DB_USER;
    }

    public static String getDatabasePassword() {
        return DB_PASSWORD;
    }
}

class DbConnectionHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange exchange) throws IOException {
        try (Connection connection = WebApp.getDatabaseConnection()) {
            String response = "Database connection established: " + connection.toString();
            sendResponse(exchange, 200, response);
        } catch (Exception e) {
            sendResponse(exchange, 500, "Failed to establish database connection.");
        }
    }
}

class ServerNameHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange exchange) throws IOException {
        String response = WebApp.getServerName();
        sendResponse(exchange, 200, response);
    }
}

class DatabaseNameHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange exchange) throws IOException {
        String response = WebApp.getDatabaseName();
        sendResponse(exchange, 200, response);
    }
}

class DatabaseUserHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange exchange) throws IOException {
        String response = WebApp.getDatabaseUser();
        sendResponse(exchange, 200, response);
    }
}

class DatabasePasswordHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange exchange) throws IOException {
        String response = WebApp.getDatabasePassword();
        sendResponse(exchange, 200, response);
    }
}

private static void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
    exchange.sendResponseHeaders(statusCode, response.getBytes().length);
    try (OutputStream os = exchange.getResponseBody()) {
        os.write(response.getBytes());
    }
}