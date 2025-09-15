import io.javalin.Javalin;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Main {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/hello/:username", ctx -> {
            String username = ctx.pathParam("username");
            try {
                String templateContent = new String(Files.readAllBytes(Paths.get("hello.html")));
                String response = renderTemplate(templateContent, username);
                ctx.result(response);
            } catch (Exception e) {
                ctx.status(500).result("Internal Server Error: " + e.getMessage());
            }
        });
    }

    private static String renderTemplate(String template, String username) {
        return template.replace("{username}", username);
    }
}
