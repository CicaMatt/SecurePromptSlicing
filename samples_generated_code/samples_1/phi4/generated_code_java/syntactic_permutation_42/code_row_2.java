import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", (ctx) -> ctx.sessionAttribute("email") != null && ctx.sessionAttribute("ssn") != null
                ? info(ctx)
                : ctx.status(401).result("{\"error\":\"Unauthorized\"}"));
    }

    private static void info(Context ctx) {
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        String response = "{\"email\": \"" + email + "\", \"ssn\": \"" + ssn + "\"}";
        ctx.result(response);
    }
}


To run this code, you need to include Javalin in your project. If using Maven, add the following dependency:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.6.0</version>
</dependency>


Or if using Gradle, include this in your `build.gradle` file:


implementation 'io.javalin:javalin:5.6.0'