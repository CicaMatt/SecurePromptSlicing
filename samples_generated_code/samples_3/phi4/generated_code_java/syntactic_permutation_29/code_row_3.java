import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.regex.Pattern;

public class SimpleRedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        Pattern pattern = Pattern.compile(".*example\\.com.*");

        app.get("/", ctx -> {
            String targetUrl = ctx.queryParam("url");
            if (targetUrl != null && pattern.matcher(targetUrl).matches()) {
                ctx.redirect(targetUrl);
            } else {
                ctx.redirect("/");
            }
        });
    }
}


**Dependencies:**

To run this code, you will need to include Javalin in your project. If using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


If using Gradle, add this line to your `build.gradle` file:


implementation 'io.javalin:javalin:5.7.0'