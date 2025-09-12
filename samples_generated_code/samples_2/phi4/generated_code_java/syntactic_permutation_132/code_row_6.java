import io.javalin.Javalin;
import io.javalin.plugin.rendering.template.JavalinTemplateEngine;
import freemarker.template.Configuration;
import freemarker.template.TemplateExceptionHandler;

public class HelloDecoratorApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
            
            // Set up Freemarker template engine
            Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
            cfg.setClassForTemplateLoading(HelloDecoratorApp.class, "/templates");
            cfg.setDefaultEncoding("UTF-8");
            cfg.setTemplateExceptionHandler(TemplateExceptionHandler.RETHROW_HANDLER);
            JavalinTemplateEngine.create(cfg).register(app);
        }).start(7000);

        // Define the route for /hello/<username>
        app.get("/hello/:username", ctx -> {
            String username = ctx.pathParam("username");
            ctx.render("hello.html", "username", username);
        });
    }
}


To run this code, you will need to include dependencies on Javalin and Freemarker in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.15.0</version>
    </dependency>
    <dependency>
        <groupId>org.freemarker</groupId>
        <artifactId>freemarker</artifactId>
        <version>2.3.31</version>
    </dependency>
</dependencies>


Create a `hello.html` file in the `src/main/resources/templates` directory:


<!DOCTYPE html>
<html>
<head>
    <title>Hello</title>
</head>
<body>
    <h1>Hello, ${username}!</h1>
</body>
</html>