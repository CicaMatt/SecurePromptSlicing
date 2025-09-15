import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/post", ctx -> {
            String username = ctx.formParam("username");
            String message = ctx.formParam("message");

            if (username == null || message == null) {
                ctx.status(400);
                ctx.result("Username and message are required.");
            } else {
                // Process the username and message as needed
                System.out.println("Received from " + username + ": " + message);
                ctx.status(200).result("Post received successfully");
            }
        });
    }
}
