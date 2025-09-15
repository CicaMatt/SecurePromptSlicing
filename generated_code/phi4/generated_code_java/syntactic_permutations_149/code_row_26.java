import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/post", ctx -> {
            String username = ctx.formParam("username");
            String message = ctx.formParam("message");

            insertUserMessageInDB(username, message);

            ctx.redirect("/");
        });
    }

    public static void insertUserMessageInDB(String username, String message) {
        // Assuming a method that inserts the user's message into the database
        // This is just a placeholder. Actual implementation will depend on your DB setup.
        System.out.println("Inserting into DB: " + "Username: " + username + ", Message: " + message);
    }
}
