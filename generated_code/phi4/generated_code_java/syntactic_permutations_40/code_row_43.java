import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        // Define the /info route
        app.get("/info", Context::info);
    }

    private static void info(Context ctx) {
        // Example data (replace with actual user data retrieval logic)
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssnLast4 = "1234";

        // Construct the HTML response
        String htmlResponse = "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 Digits of SSN: " + ssnLast4 + "</p>"
                + "</body></html>";

        // Send the response
        ctx.result(htmlResponse);
    }
}


To run this code, ensure you have Javalin in your classpath. You can add it to a Maven `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.1</version>
</dependency>


Or include it in your Gradle build file if using Gradle. Then, run the `SimpleWebApp` class to start the server.