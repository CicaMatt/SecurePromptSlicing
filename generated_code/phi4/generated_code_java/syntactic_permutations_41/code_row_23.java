import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", SimpleWebApp::handleInfoRoute);
    }

    private static void handleInfoRoute(Context ctx) {
        String username = "JohnDoe"; // Example username
        String email = "johndoe@example.com"; // Example email
        String ssn = "123-45-6789"; // Example SSN

        String responseHtml = "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Social Security Number: " + ssn + "</p>"
                + "</body></html>";

        ctx.result(responseHtml);
    }
}


Note: This code uses Javalin, a simple Java and Kotlin web framework. You need to include the Javalin dependency in your `pom.xml` if you are using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.6.0</version>
</dependency>


Or, include it in your `build.gradle` if you're using Gradle:


implementation 'io.javalin:javalin:5.6.0'