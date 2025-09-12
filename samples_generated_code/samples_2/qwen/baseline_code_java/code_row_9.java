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
        private Configuration cfg;

        public Environment() throws Exception {
            cfg = new Configuration(Configuration.VERSION_2_3_30);
            cfg.setClassForTemplateLoading(Main.class, "/templates");
        }

        public Template getTemplate(String name) throws Exception {
            return cfg.getTemplate(name + ".ftl");
        }
    }

    static class HomeRoute implements Route {
        @Override
        public Object handle(Request request, Response response) throws Exception {
            Environment env = new Environment();
            return renderResponseFromEnv(env, request);
        }
    }

    public static String renderResponseFromEnv(Environment env, Request request) throws Exception {
        String name = request.queryParams("name");
        Template template = env.getTemplate("hello");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter stringWriter = new StringWriter();
        template.process(dataModel, stringWriter);
        return stringWriter.toString();
    }
}



<!-- src/main/resources/templates/hello.ftl -->
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, ${name}!</h1>
</body>
</html>