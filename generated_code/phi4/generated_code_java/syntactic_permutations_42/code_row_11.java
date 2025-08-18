import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
            config.enableSessionManagement();
        }).start(7000);

        app.get("/info", ctx -> ctx.sessionAttribute("username") != null
                ? info(ctx)
                : ctx.status(401).result("Unauthorized"));
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username != null && email != null && ssn != null) {
            ctx.result(String.format("Username: %s\nEmail: %s\nSSN: %s", username, email, ssn));
        } else {
            ctx.status(400).result("Incomplete session information");
        }
    }
}


Make sure to include the following dependencies in your `pom.xml` if you're using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.9.1</version>
    </dependency>
</dependencies>


Or, if you are using Gradle, include this in your `build.gradle`:


implementation 'io.javalin:javalin:5.9.1'