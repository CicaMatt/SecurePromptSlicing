import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> {
            String username = "JohnDoe"; // Example username
            String email = "john.doe@example.com"; // Example email
            String ssn = "123-45-6789"; // Example SSN

            String response = "<html><body>" +
                    "<h1>User Information</h1>" +
                    "<p>Username: " + username + "</p>" +
                    "<p>Email: " + email + "</p>" +
                    "<p>Social Security Number: " + ssn + "</p>" +
                    "</body></html>";

            ctx.result(response);
        });
    }
}


To run this code, ensure you have Javalin in your project's dependencies. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.10.1</version>
</dependency>


If using Gradle, add this to your `build.gradle`:


implementation 'io.javalin:javalin:5.10.1'