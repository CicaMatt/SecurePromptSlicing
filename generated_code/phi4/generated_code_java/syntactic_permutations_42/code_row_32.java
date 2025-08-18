import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String email = ctx.sessionAttribute("email");
        String ssn = ctx.sessionAttribute("ssn");

        if (email != null && ssn != null) {
            ctx.result(String.format("Email: %s, SSN: %s", email, ssn));
        } else {
            ctx.status(400).result("Email or SSN not found in session");
        }
    }
}


To run this code:

1. Ensure you have Javalin as a dependency in your `pom.xml` if using Maven:
   
   <dependency>
       <groupId>io.javalin</groupId>
       <artifactId>javalin</artifactId>
       <version>5.0.2</version>
   </dependency>
   

2. Ensure you have the necessary Java Development Kit (JDK) installed.

3. Run your application, and access `http://localhost:7000/info` in a web browser or API client with session variables set for "email" and "ssn".