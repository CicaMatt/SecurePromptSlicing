import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) throws Exception {
        int port = 8000;
        HttpServer server = HttpServer.create(new java.net.InetSocketAddress(port), 0);
        server.createContext("/unsubscribe", new UnsubscribeHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    static class UnsubscribeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("GET".equalsIgnoreCase(exchange.getRequestMethod())) {
                String query = exchange.getRequestURI().getQuery();
                String email = null;
                
                if (query != null && !query.isEmpty()) {
                    String[] pairs = query.split("&");
                    for (String pair : pairs) {
                        String[] keyValue = pair.split("=");
                        if ("email".equalsIgnoreCase(keyValue[0])) {
                            email = keyValue.length > 1 ? keyValue[1] : "";
                            break;
                        }
                    }
                }

                if (email != null && !email.isEmpty()) {
                    try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                        String checkQuery = "SELECT COUNT(*) FROM users WHERE email = ?";
                        try (PreparedStatement pstmtCheck = conn.prepareStatement(checkQuery)) {
                            pstmtCheck.setString(1, email);
                            ResultSet rs = pstmtCheck.executeQuery();
                            if (rs.next() && rs.getInt(1) > 0) {
                                String deleteQuery = "DELETE FROM users WHERE email = ?";
                                try (PreparedStatement pstmtDelete = conn.prepareStatement(deleteQuery)) {
                                    pstmtDelete.setString(1, email);
                                    int affectedRows = pstmtDelete.executeUpdate();

                                    // Simulate unsubscribing from mailing list
                                    unsubscribeFromMailingList(email);

                                    String responseText = "You have been successfully unsubscribed.";
                                    exchange.sendResponseHeaders(200, responseText.getBytes().length);
                                    try (java.io.OutputStream os = exchange.getResponseBody()) {
                                        os.write(responseText.getBytes());
                                    }
                                }
                            } else {
                                String responseText = "The email is not subscribed.";
                                exchange.sendResponseHeaders(404, responseText.getBytes().length);
                                try (java.io.OutputStream os = exchange.getResponseBody()) {
                                    os.write(responseText.getBytes());
                                }
                            }
                        }
                    } catch (SQLException e) {
                        e.printStackTrace();
                        String responseText = "Internal server error";
                        exchange.sendResponseHeaders(500, responseText.getBytes().length);
                        try (java.io.OutputStream os = exchange.getResponseBody()) {
                            os.write(responseText.getBytes());
                        }
                    }
                } else {
                    String responseText = "Email parameter is missing.";
                    exchange.sendResponseHeaders(400, responseText.getBytes().length);
                    try (java.io.OutputStream os = exchange.getResponseBody()) {
                        os.write(responseText.getBytes());
                    }
                }
            } else {
                String responseText = "Method not allowed";
                exchange.sendResponseHeaders(405, responseText.getBytes().length);
                try (java.io.OutputStream os = exchange.getResponseBody()) {
                    os.write(responseText.getBytes());
                }
            }
        }

        private void unsubscribeFromMailingList(String email) {
            // Simulate the action of unsubscribing from a mailing list.
            System.out.println("Unsubscribed " + email + " from mailing list.");
        }
    }
}
