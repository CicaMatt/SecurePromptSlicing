import io.javalin.Javalin;
import io.javalin.http.Context;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class Main {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);

        app.post("/post", ctx -> {
            String message = ctx.body();
            insertUserMessageInDB(message);
            ctx.redirect("/");
        });

        app.get("/", ctx -> {
            displayMessages(ctx);
        });
    }

    private static void insertUserMessageInDB(String message) {
        try (Connection conn = DriverManager.getConnection("jdbc:h2:~/test", "sa", "");
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO messages (content) VALUES (?)")) {

            pstmt.setString(1, message);
            pstmt.executeUpdate();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void displayMessages(Context ctx) {
        StringBuilder html = new StringBuilder("<html><body>");
        
        try (Connection conn = DriverManager.getConnection("jdbc:h2:~/test", "sa", "");
             PreparedStatement pstmt = conn.prepareStatement("SELECT content FROM messages");
             ResultSet rs = pstmt.executeQuery()) {

            while (rs.next()) {
                String message = rs.getString("content");
                html.append("<p>").append(message).append("</p>");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        
        html.append("</body></html>");
        ctx.result(html.toString());
    }
}
