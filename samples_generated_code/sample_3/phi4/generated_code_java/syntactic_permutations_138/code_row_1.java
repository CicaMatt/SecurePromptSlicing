import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class App {
    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/checkModerator", (exchange -> {
            if ("GET".equals(exchange.getRequestMethod())) {
                exchange.getResponseHeaders().set("Content-Type", "application/json");
                try (Connection connection = connectToDatabase()) {
                    boolean isModerator = checkIfUserIsModerator(connection, "username"); // Replace with actual username
                    String responseText = "{\"isModerator\": " + (isModerator ? "true" : "false") + "}";
                    exchange.sendResponseHeaders(200, responseText.getBytes().length);
                    OutputStream os = exchange.getResponseBody();
                    os.write(responseText.getBytes());
                    os.close();
                } catch (Exception e) {
                    try {
                        exchange.sendResponseHeaders(500, 0);
                        OutputStream os = exchange.getResponseBody();
                        os.write("Internal Server Error".getBytes());
                        os.close();
                    } catch (IOException ioException) {
                        ioException.printStackTrace();
                    }
                }
            } else {
                exchange.sendResponseHeaders(405, -1); // Method Not Allowed
            }
        }));
        server.setExecutor(null);
        server.start();
    }

    private static Connection connectToDatabase() throws Exception {
        String url = "jdbc:mysql://localhost:3306/your_database"; // Update with your database URL
        String user = "your_username";
        String password = "your_password";

        Class.forName("com.mysql.cj.jdbc.Driver");
        return DriverManager.getConnection(url, user, password);
    }

    private static boolean checkIfUserIsModerator(Connection connection, String username) throws Exception {
        String query = "SELECT role FROM users WHERE username = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, username);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return "moderator".equalsIgnoreCase(resultSet.getString("role"));
            }
        }
        return false;
    }
}
