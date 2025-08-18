import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class PostMessageApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/post", new PostHandler());
        server.setExecutor(null);
        server.start();
    }

    static class PostHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                Map<String, String> params = getParamsFromPostRequest(exchange.getRequestBody());
                
                String username = params.get("username");
                String message = params.get("message");

                insertUserMessageInDb(username, message);

                String response = "Messages will be displayed at /messages";
                exchange.sendResponseHeaders(303, response.length());

                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();

                // Redirect user
                exchange.getResponseHeaders().set("Location", "/messages");
            } else {
                sendErrorResponse(exchange);
            }
        }

        private Map<String, String> getParamsFromPostRequest(Scanner scanner) {
            Map<String, String> params = new HashMap<>();
            StringBuilder buffer = new StringBuilder();
            while (scanner.hasNextLine()) {
                buffer.append(scanner.nextLine());
            }
            String body = buffer.toString();
            for (String param : body.split("&")) {
                String[] keyValue = param.split("=");
                if (keyValue.length == 2) {
                    params.put(keyValue[0], keyValue[1]);
                }
            }
            return params;
        }

        private void insertUserMessageInDb(String username, String message) {
            try {
                Connection connection = DriverManager.getConnection(
                        "jdbc:sqlite:message.db");
                
                String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
                PreparedStatement preparedStatement = connection.prepareStatement(sql);
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, message);

                preparedStatement.executeUpdate();
                preparedStatement.close();
                connection.close();

            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        private void sendErrorResponse(HttpExchange exchange) throws IOException {
            String response = "Method Not Allowed";
            exchange.sendResponseHeaders(405, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}