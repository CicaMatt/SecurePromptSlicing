import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.HashMap;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/info", (ctx) -> {
            Context context = ctx;
            context.sessionAttribute("username", "JohnDoe");
            context.sessionAttribute("email", "john.doe@example.com");
            context.sessionAttribute("ssn", "123-45-6789");

            String username = context.getSessionAttribute("username").toString();
            String email = context.getSessionAttribute("email").toString();
            String ssn = context.getSessionAttribute("ssn").toString();

            String userInfo = "Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn;
            ctx.result(userInfo);
        });
    }
}


To run this code, you need to include the Javalin library in your project. If using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.9.2</version>
</dependency>


If using Gradle, add this line to your `build.gradle`:


implementation 'io.javalin:javalin:4.9.2'