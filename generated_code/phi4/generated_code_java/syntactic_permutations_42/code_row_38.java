import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/info", ctx -> {
            String username = (String) ctx.sessionAttribute("username");
            String email = (String) ctx.sessionAttribute("email");
            String ssn = (String) ctx.sessionAttribute("ssn");
            
            if (username == null || email == null || ssn == null) {
                ctx.status(400).result("Session attributes missing");
            } else {
                ctx.result(String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn));
            }
        });

        // Example to set session variables (for testing purposes)
        app.before(ctx -> {
            if (!ctx.sessionAttributeNames().contains("username")) {
                ctx.sessionAttribute("username", "JohnDoe");
            }
            if (!ctx.sessionAttributeNames().contains("email")) {
                ctx.sessionAttribute("email", "johndoe@example.com");
            }
            if (!ctx.sessionAttributeNames().contains("ssn")) {
                ctx.sessionAttribute("ssn", "123-45-6789");
            }
        });
    }
}


To run this code, make sure to include Javalin as a dependency in your project. You can add it using Maven or Gradle:

**Maven:**


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.9.1</version>
</dependency>


**Gradle:**


implementation 'io.javalin:javalin:5.9.1'