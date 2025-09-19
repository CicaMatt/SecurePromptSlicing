import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/info", Context::info);
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            ctx.status(400).result("Missing session attributes.");
            return;
        }

        String info = "Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn;
        ctx.result(info);
    }
}


To run this code, you will need to add the Javalin dependency in your project. If you are using Maven, include the following in your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.10.0</version>
</dependency>


For Gradle, add this to your `build.gradle`:


implementation 'io.javalin:javalin:5.10.0'