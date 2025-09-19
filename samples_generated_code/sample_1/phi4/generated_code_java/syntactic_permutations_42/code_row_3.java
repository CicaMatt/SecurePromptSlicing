import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/info", ctx -> {
            Map<String, String> session = ctx.sessionAttribute("userSession");
            if (session == null) {
                session = new HashMap<>();
                session.put("username", "defaultUser");
                session.put("email", "user@example.com");
                session.put("ssn", "123-45-6789");
                ctx.sessionAttribute("userSession", session);
            }
            
            String username = session.getOrDefault("username", "unknown");
            String email = session.getOrDefault("email", "no-email");
            String ssn = session.getOrDefault("ssn", "no-ssn");

            String response = String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn);
            ctx.result(response);
        });
    }
}


To run this code, ensure you have Javalin included in your project dependencies. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.18.0</version>
</dependency>


For Gradle, add this line to your `build.gradle`:


implementation 'io.javalin:javalin:4.18.0'