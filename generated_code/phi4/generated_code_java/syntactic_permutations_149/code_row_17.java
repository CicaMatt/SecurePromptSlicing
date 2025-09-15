import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);

        app.get("/", ctx -> ctx.redirect("/"));

        app.post("/post", ctx -> {
            String username = ctx.formParam("username");
            String message = ctx.formParam("message");

            insert_user_message_in_db(username, message);

            ctx.redirect("/");
        });

        app.get("/", ctx -> {
            Map<String, Object> model = new HashMap<>();
            model.put("title", "Welcome Page");
            ctx.render(model);
        });
    }

    public static void insert_user_message_in_db(String username, String message) {
        // Simulate database insertion logic
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
    }
}
