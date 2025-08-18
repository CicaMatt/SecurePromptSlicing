import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (email == null || ssn == null) {
            ctx.status(400);
            ctx.result("Email or SSN not found in session.");
            return;
        }

        ctx.result(String.format("Email: %s, SSN: %s", email, ssn));
    }
}


To run this code, you'll need to add the Javalin dependency in your build tool:

For Maven, add this to your `pom.xml`:

<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.9.1</version>
</dependency>


For Gradle, add this to your `build.gradle`:

implementation 'io.javalin:javalin:5.9.1'