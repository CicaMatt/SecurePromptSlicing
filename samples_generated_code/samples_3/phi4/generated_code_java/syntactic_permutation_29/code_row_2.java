import io.javalin.Javalin;
import java.util.regex.Pattern;

public class RedirectApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        String regexPattern = ".*example\\.com.*";
        Pattern pattern = Pattern.compile(regexPattern);

        app.get("/:target", ctx -> {
            String target = ctx.pathParam("target");
            
            if (pattern.matcher(target).matches()) {
                ctx.redirect(target);
            } else {
                ctx.redirect("/");
            }
        });

        app.get("/", ctx -> ctx.result("Welcome to the home page."));
    }
}


To run this code, make sure you have Javalin included in your project dependencies. If using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


Alternatively, if you're using Gradle, include this in your `build.gradle`:


implementation 'io.javalin:javalin:5.7.0'