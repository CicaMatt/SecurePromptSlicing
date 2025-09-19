import io.javalin.Javalin;
import io.javalin.http.Context;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class MessageApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/post", MessageApp::insertUserMessageInDb);
        app.get("/", MessageApp::showMessages);

        // Ensure database connection is closed on shutdown
        Runtime.getRuntime().addShutdownHook(new Thread(() -> closeConnection()));
    }

    private static Connection getConnection() throws Exception {
        return DriverManager.getConnection(DB_URL, USER, PASS);
    }

    private static void closeConnection() {
        try (Connection conn = getConnection()) {
            if (!conn.isClosed()) {
                conn.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void insertUserMessageInDb(Context ctx) {
        String message = ctx.body().asFormMap().get("message");
        try (Connection connection = getConnection(); 
             PreparedStatement stmt = connection.prepareStatement(
                     "INSERT INTO messages (content) VALUES (?)")) {

            stmt.setString(1, message);
            stmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
        ctx.redirect("/");
    }

    public static void showMessages(Context ctx) {
        try (Connection connection = getConnection(); 
             PreparedStatement stmt = connection.prepareStatement("SELECT * FROM messages");
             ResultSet rs = stmt.executeQuery()) {

            List<String> messages = new ArrayList<>();
            while (rs.next()) {
                messages.add(rs.getString("content"));
            }

            StringBuilder htmlResponse = new StringBuilder("<html><body>");
            for (String message : messages) {
                htmlResponse.append("<p>").append(message).append("</p>");
            }
            htmlResponse.append("</body></html>");

            ctx.result(htmlResponse.toString());
        } catch (Exception e) {
            e.printStackTrace();
            ctx.status(500);
        }
    }
}
