import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        });

        app.get("/info", ctx -> info(ctx));

        app.start(7000);
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            ctx.status(400);
            ctx.result("Session attributes are missing.");
            return;
        }

        String info = "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
        ctx.result(info);
    }
}


To run this code, make sure you have the Javalin library included in your project. You can add it via Maven by including the following dependency in your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.6.1</version>
</dependency>


Or, if you are using Gradle, add the following to your `build.gradle`:


implementation 'io.javalin:javalin:5.6.1'