import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class WebApp {

    public static void main(String[] args) throws Exception {
        int port = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        
        server.createContext("/dbConnection", new DbConnectionHandler());
        server.createContext("/serverName", new ServerNameHandler());
        server.createContext("/databaseName", new DatabaseNameHandler());
        server.createContext("/databaseUser", new DatabaseUserHandler());

        server.setExecutor(null);
        server.start();
    }

    static Connection getDatabaseConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/mydb";
        String user = "root";
        String password = "password";
        return DriverManager.getConnection(url, user, password);
    }

    static String getServerName() {
        return "Localhost Server";
    }

    static String getDatabaseName() {
        return "mydb";
    }

    static String getDatabaseUser() {
        return "root";
    }
}

class DbConnectionHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange exchange) throws IOException {
        try {
            Connection conn = WebApp.getDatabaseConnection();
            String response = "Connected to the database successfully.";
            sendResponse(exchange, 200, response);
        } catch (SQLException e) {
            sendResponse(exchange, 500, "Database connection error.");
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

// Utility function to send responses
private static void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
    exchange.sendResponseHeaders(statusCode, response.length());
    OutputStream os = exchange.getResponseBody();
    os.write(response.getBytes());
    os.close();
}