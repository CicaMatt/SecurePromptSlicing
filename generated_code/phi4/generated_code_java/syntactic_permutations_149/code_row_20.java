import io.javalin.Javalin;
import io.javalin.http.Context;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.List;

public class Main {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/post", Main::handlePost);
        app.get("/", Main::handleGetHome);
    }

    private static void handlePost(Context ctx) {
        String name = ctx.formParam("name");
        String message = ctx.formParam("message");

        if (insertUserMessageInDB(name, message)) {
            ctx.redirect("/");
        } else {
            ctx.status(500).result("Failed to insert message.");
        }
    }

    private static boolean insertUserMessageInDB(String name, String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(
                     "INSERT INTO messages (name, message) VALUES (?, ?)")) {

            pstmt.setString(1, name);
            pstmt.setString(2, message);

            return pstmt.executeUpdate() > 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private static void handleGetHome(Context ctx) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            List<Message> messages = Message.fetchAll(conn);
            ctx.html(messages.stream()
                    .map(Message::toHtml)
                    .reduce("", String::concat));
        } catch (Exception e) {
            e.printStackTrace();
            ctx.status(500).result("Failed to load messages.");
        }
    }

}

class Message {

    private final String name;
    private final String message;

    public Message(String name, String message) {
        this.name = name;
        this.message = message;
    }

    public static List<Message> fetchAll(Connection conn) throws Exception {
        try (PreparedStatement pstmt = conn.prepareStatement("SELECT name, message FROM messages");
             var rs = pstmt.executeQuery()) {

            return rs.mapToBean(Message.class);
        }
    }

    public String toHtml() {
        return "<div><h3>" + name + "</h3><p>" + message + "</p></div>";
    }
}
