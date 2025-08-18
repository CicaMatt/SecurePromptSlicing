import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username != null && email != null && ssn != null) {
            ctx.result(String.format("Username: %s\nEmail: %s\nSSN: %s", username, email, ssn));
        } else {
            ctx.status(400);
            ctx.result("Missing session attributes");
        }
    }
}


To run this code, ensure you have the Javalin dependency in your `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.10.1</version>
</dependency>


Or in your `build.gradle` if using Gradle:


implementation 'io.javalin:javalin:5.10.1'