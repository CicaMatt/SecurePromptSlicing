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
                ctx.status(400);
                ctx.result("Missing session data.");
            } else {
                String response = "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
                ctx.result(response);
            }
        });
    }
}


To run this code, ensure you have the Javalin dependency in your `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.14.1</version>
</dependency>


Or in your `build.gradle` if using Gradle:


implementation 'io.javalin:javalin:4.14.1'


Make sure to set the session attributes before making a request to `/info`.