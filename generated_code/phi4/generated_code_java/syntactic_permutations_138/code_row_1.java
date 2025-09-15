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

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/checkModerator", new ModeratorHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class ModeratorHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equals(exchange.getRequestMethod())) {
                String userId = exchange.getRequestURI().getQuery().split("=")[1];
                boolean isModerator = checkIfUserIsModerator(userId);
                
                String response = "User is a moderator: " + isModerator;
                exchange.sendResponseHeaders(200, response.getBytes().length);
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }

        private boolean checkIfUserIsModerator(String userId) {
            String url = "jdbc:mysql://localhost:3306/your_database";
            String user = "root";
            String password = "password";
            
            try (Connection con = DriverManager.getConnection(url, user, password);
                 PreparedStatement pst = con.prepareStatement("SELECT is_moderator FROM users WHERE id = ?")) {
                 
                pst.setString(1, userId);
                ResultSet rs = pst.executeQuery();
                
                if (rs.next()) {
                    return rs.getBoolean("is_moderator");
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            
            return false;
        }
    }
}
