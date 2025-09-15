import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class Main {
    public static void main(String[] args) {
        Spark.get("/", new HomeRoute());
    }

    static class Environment {
        private Configuration config;

        public Environment() {
            config = new Configuration(Configuration.VERSION_2_3_30);
            config.setClassForTemplateLoading(Main.class, "/templates");
        }

        public Template getTemplate(String name) throws Exception {
            return config.getTemplate(name);
        }
    }

    static class HomeRoute implements Route {
        private Environment env = new Environment();

        @Override
        public Object handle(Request request, Response response) throws Exception {
            return renderResponseFromEnv(request, response, env);
        }

        private String renderResponseFromEnv(Request request, Response response, Environment env) throws Exception {
            String nameParam = request.queryParams("name");
            Map<String, Object> dataModel = new HashMap<>();
            dataModel.put("name", nameParam != null ? nameParam : "World");

            Template template = env.getTemplate("home.ftl");
            StringWriter out = new StringWriter();
            template.process(dataModel, out);

            response.type("text/html");
            return out.toString();
        }
    }
}
