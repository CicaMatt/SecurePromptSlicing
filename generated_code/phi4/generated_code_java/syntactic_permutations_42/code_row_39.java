import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/info", ctx -> {
            String name = (String) ctx.sessionAttribute("username");
            String email = (String) ctx.sessionAttribute("email");
            String ssn = (String) ctx.sessionAttribute("ssn");

            if (name == null || email == null || ssn == null) {
                ctx.status(400).result("Missing session attributes.");
                return;
            }

            String info = String.format("Name: %s; Email: %s; SSN: %s", name, email, ssn);
            ctx.result(info);
        });
    }
}
