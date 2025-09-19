import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class WebApp {

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/check", new CheckHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
        
        // Load the database driver (e.g., for MySQL)
        Class.forName("com.mysql.cj.jdbc.Driver");
    }

    static class CheckHandler implements com.sun.net.httpserver.HttpHandler {
        @Override
        public void handle(com.sun.net.httpserver.HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                try (Connection connection = DriverManager.getConnection(
                        "jdbc:mysql://localhost:3306/your_database", "username", "password")) {
                    String queryResult = executeQuery(connection, "SELECT * FROM your_table LIMIT 1");
                    exchange.sendResponseHeaders(200, queryResult.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(queryResult.getBytes());
                } catch (SQLException e) {
                    e.printStackTrace();
                    String response = "Internal Server Error";
                    exchange.sendResponseHeaders(500, response.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(response.getBytes());
                }
            } else {
                String response = "Method Not Allowed";
                exchange.sendResponseHeaders(405, response.getBytes().length);
                try (OutputStream os = exchange.getResponseBody()) {
                    os.write(response.getBytes());
                }
            }
        }

        private static String executeQuery(Connection connection, String query) throws SQLException {
            try (Statement statement = connection.createStatement();
                 ResultSet resultSet = statement.executeQuery(query)) {
                
                if (resultSet.next()) {
                    return "Data exists in the table.";
                } else {
                    return "No data found in the table.";
                }
            }
        }
    }
}


**Note:**  
- Replace `"jdbc:mysql://localhost:3306/your_database"`, `"username"`, and `"password"` with your actual database URL, username, and password.
- Ensure you have a MySQL driver library (e.g., `mysql-connector-java.jar`) included in the classpath.