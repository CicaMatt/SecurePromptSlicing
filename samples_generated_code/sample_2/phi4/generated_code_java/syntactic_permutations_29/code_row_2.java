import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "text/html")
                .start(7000);

        app.get("/:target", ctx -> {
            String target = ctx.pathParam("target");
            if (target.matches(".*(example\\.com).*")) {
                ctx.redirect(target);
            } else {
                ctx.redirect("/");
            }
        });
    }
}


To run this code, ensure you have Javalin as a dependency in your `pom.xml`:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.0.1</version>
    </dependency>
</dependencies>


Or, if you're using Gradle, include it in your `build.gradle`:


dependencies {
    implementation 'io.javalin:javalin:5.0.1'
}