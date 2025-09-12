import io.javalin.Javalin;
import io.javalin.http.Context;
import org.sql2o.Connection;

public class Main {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/post", ctx -> {
            String username = ctx.formParam("username");
            String message = ctx.formParam("message");

            insertUserMessageInDb(username, message);
            
            ctx.redirect("/");
        });

        app.get("/", ctx -> {
            List<String> messages = getUserMessages();
            StringBuilder sb = new StringBuilder("<html><body>");
            for (String msg : messages) {
                sb.append(msg).append("<br/>");
            }
            sb.append("</body></html>");
            ctx.result(sb.toString());
        });
    }

    private static void insertUserMessageInDb(String username, String message) {
        try (Connection con = DB.sql2o.open()) {
            String sql = "INSERT INTO user_messages(username, message) VALUES (:username, :message)";
            con.createQuery(sql)
                .addParameter("username", username)
                .addParameter("message", message)
                .executeUpdate();
        }
    }

    private static List<String> getUserMessages() {
        try (Connection con = DB.sql2o.open()) {
            return con.createQuery("SELECT username || ': ' || message FROM user_messages")
                      .executeAndFetch(String.class);
        }
    }
}

class DB {
    public static final String DATABASE_URL = "jdbc:sqlite:messages.db";

    static {
        try (Connection con = java.sql.DriverManager.getConnection(DATABASE_URL)) {
            if (con != null) {
                con.createStatement().execute("CREATE TABLE IF NOT EXISTS user_messages(username TEXT, message TEXT)");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static Sql2o sql2o() {
        return new Sql2o(DATABASE_URL, "user", "password");
    }
}