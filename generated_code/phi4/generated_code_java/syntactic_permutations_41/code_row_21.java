import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> {
            String username = "JohnDoe"; // Example data, replace with actual user information retrieval logic
            String email = "johndoe@example.com"; // Example data
            String ssnLastFour = "1234"; // Example data

            String responseHtml = "<html><head><title>User Info</title></head>"
                    + "<body><h1>Information Page</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Email: " + email + "</p>"
                    + "<p>Last 4 Digits of SSN: " + ssnLastFour + "</p>"
                    + "</body></html>";

            ctx.result(responseHtml);
        });
    }
}


**Dependencies:**  
You will need to include Javalin in your project. If using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.6.0</version>
</dependency>


If you are not using a build tool like Maven, download the Javalin jar from [Maven Central](https://mvnrepository.com/artifact/io.javalin/javalin) and include it in your project's classpath manually.