import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        // Sample user data, replace with actual storage logic if needed.
        String username = "johndoe";
        String email = "john.doe@example.com";
        String ssnLast4 = "1234";

        app.get("/info", ctx -> {
            Context context = ctx;
            context.result("Username: " + username + "<br>Email: " + email + "<br>Last 4 Digits of SSN: " + ssnLast4);
        });
    }
}
