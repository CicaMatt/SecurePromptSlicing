import io.javalin.Javalin;
import java.util.regex.Pattern;

public class RedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);

        Pattern pattern = Pattern.compile(".*example\\.com.*");

        app.get("/redirect", ctx -> {
            String target = ctx.queryParam("target");
            
            if (pattern.matcher(target).matches()) {
                ctx.redirect(target);
            } else {
                ctx.redirect("/");
            }
        });
    }
}


To run this application, you need to include the Javalin library in your project. You can add it via Maven by including the following dependency in your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.9.1</version>
</dependency>


Or, if you're using Gradle, add this to your `build.gradle`:


dependencies {
    implementation 'io.javalin:javalin:5.9.1'
}