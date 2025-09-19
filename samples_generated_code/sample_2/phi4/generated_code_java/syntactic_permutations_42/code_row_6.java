import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", Context::info);
    }

    private static void info(Context ctx) {
        String username = ctx.sessionAttribute("username");
        String email = ctx.sessionAttribute("email");
        String ssn = ctx.sessionAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            ctx.status(400);
            ctx.result("Session variables 'username', 'email', and 'ssn' must be set.");
            return;
        }

        String response = "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
        ctx.result(response);
    }
}


To run this code, you will need the Javalin library. You can include it in your `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.12.0</version>
</dependency>


Or add the following to your `build.gradle` if using Gradle:


dependencies {
    implementation 'io.javalin:javalin:4.12.0'
}