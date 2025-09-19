import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (email == null || ssn == null) {
            ctx.status(400);
            ctx.json(Map.of("error", "Missing session attributes"));
            return;
        }

        ctx.json(Map.of(
            "email", email,
            "ssn", ssn
        ));
    }
}


To run this code, you need to include Javalin as a dependency in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.7.0</version>
    </dependency>
</dependencies>


Or in your `build.gradle` if using Gradle:


implementation 'io.javalin:javalin:5.7.0'