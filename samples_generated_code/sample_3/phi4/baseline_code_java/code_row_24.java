import io.javalin.Javalin;
import spark.template.handlebars.HandlebarsTemplateEngine;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.staticFiles.enableWebJars()).start(7000);

        app.get("/info", ctx -> {
            String username = "JohnDoe"; // Example username
            String email = "john.doe@example.com"; // Example email
            String ssnLastFour = "1234"; // Example last 4 digits of SSN

            // Render the information using Handlebars template engine
            String html = new HandlebarsTemplateEngine().render(
                "templates/info.mustache",
                Map.of(
                    "username", username,
                    "email", email,
                    "ssnLastFour", ssnLastFour
                )
            );

            ctx.html(html);
        });
    }
}
