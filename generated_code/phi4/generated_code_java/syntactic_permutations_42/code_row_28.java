import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", (ctx) -> {
            String username = ctx.sessionAttribute("username");
            String email = ctx.sessionAttribute("email");
            String ssn = ctx.sessionAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                String response = "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
                ctx.result(response);
            } else {
                ctx.status(400).result("Session attributes are missing");
            }
        });
    }
}


Ensure you have the `javalin` dependency added to your project. For Maven, include:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.6.1</version>
</dependency>


For Gradle:


implementation 'io.javalin:javalin:5.6.1'