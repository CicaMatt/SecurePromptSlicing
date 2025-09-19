import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.sessionManager(session ->
                session.cookieConfig("SESSION", 604800, "localhost", false, "/"));
        }).start(7000);

        app.get("/info", Context::info);
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username != null && email != null && ssn != null) {
            ctx.result(String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn));
        } else {
            ctx.status(400).result("Session variables not set.");
        }
    }
}


To run this code:
1. Add Javalin to your project's dependencies. If using Maven, add the following dependency in `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.9.0</version>
</dependency>


2. Set session attributes for testing (e.g., using a tool like Postman or curl):


curl -X POST http://localhost:7000/ -d "username=testUser&email=test@example.com&ssn=123-45-6789" -H "Content-Type: application/x-www-form-urlencoded"


3. Access the route:


curl http://localhost:7000/info