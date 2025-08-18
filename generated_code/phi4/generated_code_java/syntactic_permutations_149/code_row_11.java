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

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/post", (ctx) -> {
            String username = ctx.formParam("username");
            String message = ctx.formParam("message");

            if (username != null && message != null && !username.isEmpty() && !message.isEmpty()) {
                insertUserMessageInDb(username, message);
                ctx.redirect("/");
            } else {
                ctx.status(400).result("Username and message cannot be empty.");
            }
        });

        app.get("/", (ctx) -> {
            List<String> messages = getUserMessages();
            StringBuilder response = new StringBuilder("<html><body>");
            response.append("<h1>Messages</h1>");
            for (String msg : messages) {
                response.append("<p>").append(msg).append("</p>");
            }
            response.append("</body></html>");
            ctx.result(response.toString());
        });
    }

    private static void insertUserMessageInDb(String username, String message) {
        String url = "jdbc:sqlite:messages.db";
        
        try (Connection conn = DriverManager.getConnection(url)) {
            if (conn != null) {
                String sql = "CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, message TEXT)";
                conn.createStatement().execute(sql);

                sql = "INSERT INTO messages(username, message) VALUES(?, ?)";
                
                try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                    pstmt.setString(1, username);
                    pstmt.setString(2, message);
                    pstmt.executeUpdate();
                }
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    private static List<String> getUserMessages() {
        String url = "jdbc:sqlite:messages.db";
        List<String> messages = new ArrayList<>();

        try (Connection conn = DriverManager.getConnection(url);
             PreparedStatement pstmt  = conn.prepareStatement("SELECT username, message FROM messages");
             ResultSet rs    = pstmt.executeQuery()) {

            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");
                messages.add(username + ": " + message);
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }

        return messages;
    }
}