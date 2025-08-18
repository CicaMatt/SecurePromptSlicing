import io.javalin.Javalin;
import io.javalin.http.Context;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class MessageApp {

    private static final String DB_URL = "jdbc:h2:mem:testdb";
    private static final String USER = "sa";
    private static final String PASS = "";

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.addStaticFiles("/public");
        }).start(7000);

        // Initialize the database
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String createTableSQL = "CREATE TABLE IF NOT EXISTS messages (" +
                    "id INT AUTO_INCREMENT PRIMARY KEY," +
                    "username VARCHAR(255) NOT NULL," +
                    "message TEXT NOT NULL" +
                    ")";
            conn.createStatement().execute(createTableSQL);
        } catch (SQLException e) {
            e.printStackTrace();
        }

        app.post("/post", ctx -> {
            String username = ctx.formParam("username");
            String message = ctx.formParam("message");

            if (username != null && message != null && !username.isEmpty() && !message.isEmpty()) {
                insertUserMessageInDb(username, message);
            }
            ctx.redirect("/");
        });

        app.get("/", ctx -> {
            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                var rs = conn.createStatement().executeQuery("SELECT username, message FROM messages");
                StringBuilder sb = new StringBuilder("<html><body><h1>Messages</h1>");
                
                while (rs.next()) {
                    String username = rs.getString("username");
                    String message = rs.getString("message");
                    sb.append("<p>").append(username).append(": ").append(message).append("</p>");
                }
                
                sb.append("</body></html>");
                ctx.result(sb.toString());
            } catch (SQLException e) {
                e.printStackTrace();
                ctx.status(500);
                ctx.result("Internal Server Error");
            }
        });
    }

    private static void insertUserMessageInDb(String username, String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, message);

            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}