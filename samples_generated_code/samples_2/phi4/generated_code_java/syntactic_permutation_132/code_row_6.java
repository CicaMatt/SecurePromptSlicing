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
