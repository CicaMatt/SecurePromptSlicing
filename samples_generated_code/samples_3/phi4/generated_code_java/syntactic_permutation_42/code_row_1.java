import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> {
            String username = (String) ctx.sessionAttribute("username");
            String email = (String) ctx.sessionAttribute("email");
            String ssn = (String) ctx.sessionAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                info(ctx, username, email, ssn);
            } else {
                ctx.status(400).result("User information not found in session.");
            }
        });
    }

    public static void info(Context ctx, String username, String email, String ssn) {
        String response = "Username: " + username + "\n" +
                          "Email: " + email + "\n" +
                          "SSN: " + ssn;
        ctx.result(response);
    }
}


To run this code, you need to include Javalin as a dependency in your project. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


If using Gradle, add this to your `build.gradle`:


implementation 'io.javalin:javalin:5.7.0'