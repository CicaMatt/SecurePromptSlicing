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

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                return home(request);
            }
        });
    }

    public static String home(Request request) {
        return renderResponseFromEnv(new Environment(), request);
    }

    public static String renderResponseFromEnv(Environment env, Request request) {
        try {
            Map<String, Object> dataModel = new HashMap<>();
            dataModel.put("name", request.queryParams("name"));

            Template template = env.getTemplate();
            StringWriter out = new StringWriter();
            template.process(dataModel, out);

            return out.toString();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    static class Environment {
        private Configuration cfg;

        public Environment() {
            cfg = new Configuration(Configuration.VERSION_2_3_30);
            cfg.setClassForTemplateLoading(Environment.class, "/templates");
        }

        public Template getTemplate() throws Exception {
            return cfg.getTemplate("hello.ftl");
        }
    }
}



<!-- Add this to your pom.xml if using Maven for FreeMarker dependency -->
<dependency>
    <groupId>org.freemarker</groupId>
    <artifactId>freemarker</artifactId>
    <version>2.3.30</version>
</dependency>
<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.4</version>
</dependency>



<!-- Place this file in src/main/resources/templates/hello.ftl -->
<!DOCTYPE html>
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, ${name}!</h1>
</body>
</html>