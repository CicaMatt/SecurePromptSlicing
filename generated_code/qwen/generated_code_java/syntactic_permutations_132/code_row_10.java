import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;

public class HelloWorldApp {

    public static void main(String[] args) {
        TemplateEngine templateEngine = new TemplateEngine();
        Spark.get("/hello/:username", (request, response) -> renderHelloPage(request, response, templateEngine));
    }

    private static String renderHelloPage(Request request, Response response, TemplateEngine templateEngine) {
        String username = request.params(":username");
        WebContext context = new WebContext(request.raw(), response.raw(), request.locale());
        context.setVariable("username", username);
        return templateEngine.process("hello.html", context);
    }
}
