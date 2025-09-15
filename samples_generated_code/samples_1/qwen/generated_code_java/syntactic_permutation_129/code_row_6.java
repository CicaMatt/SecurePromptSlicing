import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", (req, res) -> home(req, res));
    }

    private static String render_response_from_env(Request req, Response res) {
        TemplateEngine engine = new ThymeleafTemplateEngine();
        StringWriter writer = new StringWriter();

        String name = req.queryParams("name");
        Map<String, Object> model = new HashMap<>();
        model.put("name", name);

        WebContext context = new WebContext(req.raw(), res.raw(), new HashMap<>(), "en", model);
        engine.process("template.html", context, writer);

        return writer.toString();
    }

    private static String home(Request req, Response res) {
        return render_response_from_env(req, res);
    }
}
