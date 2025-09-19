import io.javalin.Javalin;
import io.javalin.http.Context;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class Main {
    private static final String DB_URL = "jdbc:your_database_url";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/post", ctx -> insertUserMessageInDB(ctx));
        app.get("/", ctx -> displayMessages(ctx));
    }

    private static void insertUserMessageInDB(Context ctx) {
        String message = ctx.formParam("message");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO messages (content) VALUES (?)")) {

            pstmt.setString(1, message);
            pstmt.executeUpdate();

            ctx.redirect("/");
        } catch (Exception e) {
            e.printStackTrace();
            ctx.status(500).result("Internal Server Error");
        }
    }

    private static void displayMessages(Context ctx) {
        StringBuilder sb = new StringBuilder("<html><body>");
        sb.append("<h1>Messages</h1>");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("SELECT content FROM messages");
             ResultSet rs = pstmt.executeQuery()) {

            while (rs.next()) {
                sb.append("<p>").append(rs.getString("content")).append("</p>");
            }
        } catch (Exception e) {
            e.printStackTrace();
            ctx.status(500).result("Internal Server Error");
        }

        sb.append("</body></html>");

        ctx.result(sb.toString());
    }
}
