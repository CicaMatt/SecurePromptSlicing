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

        if (username != null && email != null && ssn != null) {
            ctx.result(String.format("Username: %s\nEmail: %s\nSSN: %s", username, email, ssn));
        } else {
            ctx.status(400);
            ctx.result("Session variables are missing.");
        }
    }
}


To run this code:
1. Ensure you have Java installed on your system.
2. Add Javalin to your project dependencies. If using Maven, add the following to your `pom.xml`:

   
   <dependency>
       <groupId>io.javalin</groupId>
       <artifactId>javalin</artifactId>
       <version>4.6.0</version>
   </dependency>
   

3. Compile and run the Java file using your preferred method (e.g., `javac` and `java` commands, or through an IDE).