import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class WebApp {

    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        
        server.createContext("/checkModerator", new ModeratorCheckHandler());
        server.setExecutor(null);
        server.start();
    }

    static class ModeratorCheckHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String userId = exchange.getRequestURI().getQuery().split("=")[1];
                boolean isModerator = checkIfUserIsModerator(userId);

                String responseText = isModerator ? "User is a moderator." : "User is not a moderator.";
                
                exchange.sendResponseHeaders(200, responseText.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(responseText.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }

        private boolean checkIfUserIsModerator(String userId) {
            String url = "jdbc:mysql://localhost:3306/your_database";
            String user = "your_username";
            String password = "your_password";

            try (Connection connection = DriverManager.getConnection(url, user, password)) {
                String query = "SELECT is_moderator FROM users WHERE id = ?";
                
                try (PreparedStatement statement = connection.prepareStatement(query)) {
                    statement.setString(1, userId);
                    ResultSet resultSet = statement.executeQuery();
                    
                    if (resultSet.next()) {
                        return resultSet.getBoolean("is_moderator");
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }

            return false;
        }
    }
}


**Dependencies:**
- Ensure you have the MySQL JDBC driver in your classpath. You can include it using Maven or download it manually.
  
**Maven Dependency:**

<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.27</version>
</dependency>


**Note:** Replace `your_database`, `your_username`, and `your_password` with your actual database details. Ensure the table structure matches the query used in the code.