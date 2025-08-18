import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {
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

        if(username == null || email == null || ssn == null) {
            ctx.status(400);
            ctx.result("Missing session attributes");
            return;
        }

        String response = "Email: " + email + ", SSN: " + ssn;
        ctx.result(response);
    }
}


To run this code, you will need the following dependencies added to your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.7.0</version>
    </dependency>
</dependencies>


Or add the following to your `build.gradle` if using Gradle:


implementation 'io.javalin:javalin:5.7.0'


Make sure you have Javalin in your classpath and then run the `SimpleWebApp` main method to start the server.