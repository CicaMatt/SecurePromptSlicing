import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) throws Exception {
        int serverPort = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(serverPort), 0);
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws Exception {
            if ("GET".equals(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String emailParam = Optional.ofNullable(query)
                        .map(q -> java.net.URLDecoder.decode(q, "UTF-8"))
                        .filter(q -> q.startsWith("email="))
                        .map(q -> q.substring(6))
                        .orElse(null);

                if (emailParam != null) {
                    try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
                        String sql = "SELECT * FROM users WHERE email = ?";
                        try (PreparedStatement statement = connection.prepareStatement(sql)) {
                            statement.setString(1, emailParam);
                            ResultSet resultSet = statement.executeQuery();
                            if (resultSet.next()) {
                                // User found, unsubscribe logic
                                String unsubscribeSql = "DELETE FROM users WHERE email = ?";
                                try (PreparedStatement deleteStatement = connection.prepareStatement(unsubscribeSql)) {
                                    deleteStatement.setString(1, emailParam);
                                    int rowsAffected = deleteStatement.executeUpdate();

                                    String responseText;
                                    if (rowsAffected > 0) {
                                        // Unsubscribe from mailing list logic here
                                        responseText = "User unsubscribed successfully.";
                                    } else {
                                        responseText = "Failed to unsubscribe user.";
                                    }
                                    sendResponse(exchange, 200, responseText);
                                }
                            } else {
                                String responseText = "The email is not subscribed.";
                                sendResponse(exchange, 404, responseText);
                            }
                        }
                    }
                } else {
                    sendResponse(exchange, 400, "Invalid request. Email parameter is missing.");
                }
            } else {
                sendResponse(exchange, 405, "Method Not Allowed");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws Exception {
            exchange.sendResponseHeaders(statusCode, response.length());
            try (var os = exchange.getResponseBody()) {
                os.write(response.getBytes());
            }
        }
    }
}
