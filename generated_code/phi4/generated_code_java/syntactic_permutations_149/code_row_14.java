import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.List;
import java.util.concurrent.Executors;

public class SimpleHttpServer {

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/post", new PostHandler());
        server.createContext("/", new IndexHandler());

        server.setExecutor(Executors.newCachedThreadPool());
        server.start();
    }

    static class PostHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestBody().toString();
                String[] params = query.split("&");
                String username = null;
                String message = null;

                for (String param : params) {
                    String[] keyValue = param.split("=");
                    if ("username".equals(keyValue[0])) {
                        username = keyValue[1];
                    } else if ("message".equals(keyValue[0])) {
                        message = keyValue[1];
                    }
                }

                try (Connection conn = DriverManager.getConnection(
                        "jdbc:h2:~/test", "sa", "")) {

                    String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
                    PreparedStatement pstmt = conn.prepareStatement(sql);
                    pstmt.setString(1, username);
                    pstmt.setString(2, message);
                    pstmt.executeUpdate();
                } catch (SQLException e) {
                    e.printStackTrace();
                }

                exchange.getResponseHeaders().set("Location", "/");
                exchange.sendResponseHeaders(302, -1);
            }
        }
    }

    static class IndexHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            StringBuilder response = new StringBuilder("<html><head><title>Messages</title></head><body>");
            response.append("<h1>Messages</h1><ul>");

            try (Connection conn = DriverManager.getConnection(
                    "jdbc:h2:~/test", "sa", "")) {

                String sql = "SELECT username, message FROM messages";
                var statement = conn.createStatement();
                var resultSet = statement.executeQuery(sql);

                while (resultSet.next()) {
                    response.append("<li>")
                            .append(resultSet.getString("username"))
                            .append(": ")
                            .append(resultSet.getString("message"))
                            .append("</li>");
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }

            response.append("</ul></body></html>");

            exchange.sendResponseHeaders(200, response.toString().getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.toString().getBytes());
            os.close();
        }
    }
}


Make sure to have the H2 database driver in your classpath. You can download it from [H2 Database Downloads](https://h2database.com/html/download.html) or include it via Maven/Gradle if you are using a build tool. Also, create the `messages` table in the H2 database beforehand:


CREATE TABLE messages (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255),
    message TEXT
);


This code sets up a simple HTTP server that handles POST requests to `/post`, inserts the message into an H2 database, and redirects back to the root path. The root path displays all messages stored in the database.