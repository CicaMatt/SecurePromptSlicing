import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/info", ctx -> {
            String email = ctx.sessionAttribute("email");
            String ssn = ctx.sessionAttribute("ssn");

            if (email == null || ssn == null) {
                ctx.status(400).result("{\"error\":\"Email or SSN not found in session.\"}");
                return;
            }

            ctx.json("{\"email\":\"" + email + "\", \"ssn\":\"" + ssn + "\"}");
        });

        // Example to set session attributes (for demonstration purposes)
        app.get("/setSession", ctx -> {
            ctx.sessionAttribute("email", "user@example.com");
            ctx.sessionAttribute("ssn", "123-45-6789");
            ctx.result("{\"message\":\"Session variables set.\"}");
        });
    }
}


To run this code, you need to include the Javalin dependency in your project. If you are using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.9.0</version>
</dependency>


If you are using Gradle, add this line to your `build.gradle` file:


implementation 'io.javalin:javalin:5.9.0'