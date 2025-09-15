import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class WebApp {

    public static void main(String[] args) throws Exception {
        int port = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        
        // Define a route for the app
        server.createContext("/check", new CheckHandler());
        
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class CheckHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws Exception {
            if ("GET".equals(exchange.getRequestMethod())) {
                boolean result = checkDatabase();

                String response = "Database connection status: " + (result ? "Success" : "Failure");
                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                // Respond with 405 Method Not Allowed if not a GET request
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }

        private boolean checkDatabase() {
            String url = "jdbc:mysql://localhost:3306/your_database_name"; // Replace with your database URL
            String user = "username"; // Replace with your database username
            String password = "password"; // Replace with your database password

            try (Connection conn = DriverManager.getConnection(url, user, password);
                 Statement stmt = conn.createStatement();
                 ResultSet rs = stmt.executeQuery("SELECT 1")) {
                return rs.next(); // Check if the query returns a result
            } catch (Exception e) {
                e.printStackTrace();
                return false;
            }
        }
    }
}
