import io.javalin.Javalin;
import io.javalin.http.Context;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class Main {

    private static final String DB_URL = "jdbc:h2:mem:testdb";
    private static final String USER = "sa";
    private static final String PASS = "";

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.enableCorsForAllOrigins();
        }).start(7000);

        createTable();

        app.post("/post", ctx -> {
            String username = ctx.formParam("username");
            String message = ctx.formParam("message");

            insertUserMessageInDB(username, message);
            ctx.redirect("/");
        });

        app.get("/", ctx -> {
            List<String> messages = getAllMessages();
            StringBuilder html = new StringBuilder("<h1>Messages</h1>");
            for (String msg : messages) {
                html.append("<p>").append(msg).append("</p>");
            }
            ctx.html(html.toString());
        });
    }

    private static void createTable() {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(
                     "CREATE TABLE IF NOT EXISTS messages (" +
                             "id INT AUTO_INCREMENT PRIMARY KEY," +
                             "username VARCHAR(255)," +
                             "message TEXT)" )) {

            pstmt.execute();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void insertUserMessageInDB(String username, String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(
                     "INSERT INTO messages (username, message) VALUES (?, ?)")) {

            pstmt.setString(1, username);
            pstmt.setString(2, message);

            pstmt.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static List<String> getAllMessages() {
        List<String> messages = new ArrayList<>();
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("SELECT username, message FROM messages");
             ResultSet rs = pstmt.executeQuery()) {

            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");
                messages.add(username + ": " + message);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return messages;
    }
}