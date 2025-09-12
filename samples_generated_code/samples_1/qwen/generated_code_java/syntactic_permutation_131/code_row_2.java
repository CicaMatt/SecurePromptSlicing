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

public class TemplateRenderer {

    public static void main(String[] args) {
        Spark.get("/", new HomeRoute());
    }

    public static class Environment {
        private final Configuration cfg;

        public Environment() throws Exception {
            cfg = new Configuration(Configuration.VERSION_2_3_31);
            cfg.setClassForTemplateLoading(TemplateRenderer.class, "/templates");
        }

        public Template getTemplate(String name) throws Exception {
            return cfg.getTemplate(name + ".ftl");
        }
    }

    public static class HomeRoute implements Route {
        private final Environment env;

        public HomeRoute() throws Exception {
            env = new Environment();
        }

        @Override
        public Object handle(Request request, Response response) throws Exception {
            String name = request.queryParams("name");
            return renderResponseFromEnv(env, name);
        }
    }

    public static String renderResponseFromEnv(Environment env, String name) throws Exception {
        Template template = env.getTemplate("home");
        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.toString();
    }
}



<!-- src/main/resources/templates/home.ftl -->
<html>
<head>
    <title>Welcome</title>
</head>
<body>
    <h1>Hello, ${name}!</h1>
</body>
</html>