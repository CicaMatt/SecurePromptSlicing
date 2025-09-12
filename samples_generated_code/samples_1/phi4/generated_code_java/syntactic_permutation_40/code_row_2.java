import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        // Sample user data, replace with actual storage logic if needed.
        String username = "johndoe";
        String email = "john.doe@example.com";
        String ssnLast4 = "1234";

        app.get("/info", ctx -> {
            Context context = ctx;
            context.result("Username: " + username + "<br>Email: " + email + "<br>Last 4 Digits of SSN: " + ssnLast4);
        });
    }
}


To run this code, you need to have Javalin as a dependency. You can include it in your `pom.xml` for Maven or `build.gradle` for Gradle.

**Maven (`pom.xml`)**

<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


**Gradle (`build.gradle`)**

implementation 'io.javalin:javalin:5.7.0'


Make sure to include the appropriate dependencies and run your application on a server that supports Java web applications.