import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/hello/{username}", ctx -> {
            String username = ctx.pathParam("username");
            String htmlContent = renderTemplate(username);
            ctx.result(htmlContent);
        });
    }

    private static String renderTemplate(String username) {
        return "<html><body>" +
                "<h1>Hello, " + username + "!</h1>" +
                "</body></html>";
    }
}


**Dependencies for running the code:**

Add the following dependency to your `pom.xml` if you are using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.14.0</version>
</dependency>


Or add this to your `build.gradle` if you are using Gradle:


implementation 'io.javalin:javalin:4.14.0'


Ensure you have a Java environment set up with Javalin library installed.