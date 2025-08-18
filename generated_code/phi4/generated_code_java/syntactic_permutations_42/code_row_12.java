import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/", ctx -> {
            String username = (String) ctx.sessionAttribute("username");
            String email = (String) ctx.sessionAttribute("email");
            String ssn = (String) ctx.sessionAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                ctx.result("Username: " + username + ", Email: " + email + ", SSN: " + ssn);
            } else {
                ctx.status(400);
                ctx.result("Missing user information in session.");
            }
        });

        // Simulate setting session attributes for demonstration purposes
        app.post("/setUserInfo", ctx -> {
            String username = ctx.formParam("username");
            String email = ctx.formParam("email");
            String ssn = ctx.formParam("ssn");

            ctx.sessionAttribute("username", username);
            ctx.sessionAttribute("email", email);
            ctx.sessionAttribute("ssn", ssn);

            ctx.result("User information set.");
        });
    }
}


Note: This code uses Javalin, a lightweight Java web framework. You need to include the Javalin dependency in your `pom.xml` if you're using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.10.1</version> <!-- or latest version -->
</dependency>


Or, in your `build.gradle` file if you're using Gradle:


dependencies {
    implementation 'io.javalin:javalin:5.10.1' // or latest version
}