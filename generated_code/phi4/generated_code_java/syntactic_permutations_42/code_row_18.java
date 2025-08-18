import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/info", ctx -> {
            String username = (String) ctx.sessionAttribute("username");
            String email = (String) ctx.sessionAttribute("email");
            String ssn = (String) ctx.sessionAttribute("ssn");

            if (username == null || email == null || ssn == null) {
                ctx.status(400);
                ctx.result("Missing session attributes.");
            } else {
                String userInfo = "Username: " + username + "\n" +
                                  "Email: " + email + "\n" +
                                  "SSN: " + ssn;
                ctx.result(userInfo);
            }
        });
    }
}


To run this code, you will need to include the Javalin dependency in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.11.0</version>
    </dependency>
</dependencies>


Or in your `build.gradle` file if using Gradle:


dependencies {
    implementation 'io.javalin:javalin:5.11.0'
}