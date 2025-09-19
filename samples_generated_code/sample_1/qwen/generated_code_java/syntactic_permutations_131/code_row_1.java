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
            public Object handle(Request request, Response response) throws Exception {
                return home(new Environment(request));
            }
        });
    }

    public static String render_response_from_env(Environment env) {
        Request request = env.getRequest();
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(WebApp.class, "/templates");

        try {
            Template template = cfg.getTemplate("template.ftl");
            Map<String, Object> dataModel = new HashMap<>();
            dataModel.put("user", request.queryParams("user"));
            StringWriter out = new StringWriter();
            template.process(dataModel, out);
            return out.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return "Error rendering template";
        }
    }

    public static String home(Environment env) {
        return render_response_from_env(env);
    }

    static class Environment {
        private Request request;

        public Environment(Request request) {
            this.request = request;
        }

        public Request getRequest() {
            return request;
        }
    }
}



<!-- pom.xml for Maven to include Spark and FreeMarker dependencies -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>webapp</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
        <dependency>
            <groupId>org.freemarker</groupId>
            <artifactId>freemarker</artifactId>
            <version>2.3.31</version>
        </dependency>
    </dependencies>
</project>



<!-- src/main/resources/templates/template.ftl -->
<!DOCTYPE html>
<html>
<head>
    <title>Welcome</title>
</head>
<body>
    <h1>Hello, ${user}!</h1>
</body>
</html>