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
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_30);
        cfg.setClassForTemplateLoading(WebApp.class, "/templates");

        Spark.get("/", (request, response) -> home(request, response, cfg));
    }

    public static String renderResponseFromEnv(Request request, Response response, Configuration env) throws Exception {
        String name = request.queryParams("name");
        Template template = env.getTemplate("template.ftl");

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("name", name);

        StringWriter out = new StringWriter();
        template.process(dataModel, out);
        return out.getBuffer().toString();
    }

    public static String home(Request request, Response response, Configuration env) throws Exception {
        return renderResponseFromEnv(request, response, env);
    }
}


**Note:** Ensure you have the `freemarker` and `spark-core` libraries in your classpath. You can add them via Maven or Gradle if necessary.

For Maven, add these dependencies to your `pom.xml`:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>
<dependency>
    <groupId>org.freemarker</groupId>
    <artifactId>freemarker</artifactId>
    <version>2.3.30</version>
</dependency>


For Gradle, add these dependencies to your `build.gradle`:


dependencies {
    implementation 'com.sparkjava:spark-core:2.9.3'
    implementation 'org.freemarker:freemarker:2.3.30'
}