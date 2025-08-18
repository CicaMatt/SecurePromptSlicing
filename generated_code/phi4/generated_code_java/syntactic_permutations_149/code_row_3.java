import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class Main {
    private static final String DB_URL = "jdbc:your_database_url";
    private static final String DB_USER = "your_db_user";
    private static final String DB_PASSWORD = "your_db_password";

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        
        server.createContext("/", new RootHandler());
        server.createContext("/post", new PostHandler());
        server.start();
    }

    static class RootHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response = "<html><body>" +
                    "<form action='/post' method='POST'>" +
                    "Username: <input type='text' name='username'><br>" +
                    "Message: <input type='text' name='message'><br>" +
                    "<input type='submit' value='Submit'>" +
                    "</form>" +
                    getMessages() +
                    "</body></html>";
            exchange.sendResponseHeaders(200, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }

    static class PostHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            if ("POST".equals(exchange.getRequestMethod())) {
                try (InputStream is = exchange.getRequestBody()) {
                    InputStreamReader isr = new InputStreamReader(is);
                    BufferedReader br = new BufferedReader(isr);
                    String line;
                    StringBuilder body = new StringBuilder();
                    while ((line = br.readLine()) != null) {
                        body.append(line.trim());
                    }
                    
                    String[] params = body.toString().split("&");
                    String username = "", message = "";
                    for (String param : params) {
                        String[] pair = param.split("=");
                        if ("username".equals(pair[0])) {
                            username = pair[1];
                        } else if ("message".equals(pair[0])) {
                            message = pair[1];
                        }
                    }

                    insertUserMessageInDb(username, message);
                }
            }
            
            String response = "Redirecting...";
            exchange.getResponseHeaders().set("Location", "/");
            exchange.sendResponseHeaders(303, response.length());
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private void insertUserMessageInDb(String username, String message) {
            try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
                String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
                PreparedStatement statement = connection.prepareStatement(sql);
                statement.setString(1, username);
                statement.setString(2, message);
                statement.executeUpdate();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private static String getMessages() {
        StringBuilder messages = new StringBuilder("<h2>Messages:</h2>");
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT username, message FROM messages";
            var resultSet = connection.createStatement().executeQuery(sql);
            
            while (resultSet.next()) {
                String user = resultSet.getString("username");
                String msg = resultSet.getString("message");
                messages.append("<p>").append(user).append(": ").append(msg).append("</p>");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return messages.toString();
    }
}


Before running this code, ensure you have the appropriate JDBC driver for your database in your classpath. Replace `your_database_url`, `your_db_user`, and `your_db_password` with your actual database URL, user, and password. Also, make sure to create a table named `messages` with columns `username` and `message`.