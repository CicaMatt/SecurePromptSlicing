import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", new HomeRoute());
    }

    public static class Environment {
        private TemplateEngine templateEngine;

        public Environment() {
            this.templateEngine = new ThymeleafTemplateEngine();
        }

        public String renderTemplate(Request request, Response response, String templateName, Map<String, Object> model) {
            StringWriter stringWriter = new StringWriter();
            WebContext context = new WebContext(request.raw(), response.raw(), request.servletContext(), request.locale(), model);
            templateEngine.process(templateName, context, stringWriter);
            return stringWriter.toString();
        }
    }

    public static class HomeRoute implements Route {
        private Environment env = new Environment();

        @Override
        public Object handle(Request request, Response response) {
            return renderResponseFromEnv(request, response);
        }

        private String renderResponseFromEnv(Request request, Response response) {
            String name = request.queryParams("name");
            Map<String, Object> model = new HashMap<>();
            model.put("name", name);
            return env.renderTemplate(request, response, "home.html", model);
        }
    }
}