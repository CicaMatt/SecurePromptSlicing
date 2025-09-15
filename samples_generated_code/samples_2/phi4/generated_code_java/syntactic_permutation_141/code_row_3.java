import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

public class WebApp {

    private static final String DB_URL = "jdbc:your_database_url";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(8000), 0);
        server.createContext("/api", new ApiHandler());
        server.start();
        
        System.out.println("Server is listening on port 8000");
    }

    private static class ApiHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "API Response\n" +
                    "Database Connection: " + getDbConnection() + "\n" +
                    "Server Name: " + getServerName() + "\n" +
                    "Database Name: " + getDatabaseName() + "\n" +
                    "Database User: " + getDatabaseUser();
            exchange.sendResponseHeaders(200, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }

    public static Connection getDbConnection() {
        try {
            return DriverManager.getConnection(DB_URL, USER, PASS);
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static String getServerName() {
        return "YourServerName";
    }

    public static String getDatabaseName() {
        // Assuming database name is part of the DB_URL
        if (DB_URL.contains(":")) {
            return DB_URL.split("/")[3];
        }
        return null;
    }

    public static String getDatabaseUser() {
        return USER;
    }
}
