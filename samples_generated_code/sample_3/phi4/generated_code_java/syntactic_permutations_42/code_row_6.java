import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> {
            String username = (String) ctx.sessionAttribute("username");
            String email = (String) ctx.sessionAttribute("email");
            String ssn = (String) ctx.sessionAttribute("ssn");

            if (username == null || email == null || ssn == null) {
                ctx.status(400);
                ctx.result("Missing session attributes: username, email, or ssn.");
            } else {
                String response = "Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn;
                ctx.result(response);
            }
        });

        // Example of setting session attributes (to be done in a different route or initialization)
        app.before(ctx -> {
            if (!ctx.sessionAttribute("username").isPresent()) {
                ctx.sessionAttribute("username", "JohnDoe");
            }
            if (!ctx.sessionAttribute("email").isPresent()) {
                ctx.sessionAttribute("email", "john.doe@example.com");
            }
            if (!ctx.sessionAttribute("ssn").isPresent()) {
                ctx.sessionAttribute("ssn", "123-45-6789");
            }
        });
    }
}


**Build and run instructions:**

1. Add Javalin dependency to your `pom.xml` if using Maven:
   
   <dependency>
       <groupId>io.javalin</groupId>
       <artifactId>javalin</artifactId>
       <version>5.0.0</version>
   </dependency>
   

2. Run the application with a Java runtime environment.