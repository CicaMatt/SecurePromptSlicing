import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> hello(request, response));
    }

    private static String hello(Request request, Response response) {
        String username = request.params(":username");
        return new freemarker.template.Configuration(freemarker.template.Configuration.VERSION_2_3_30)
                .getTemplate("hello.html")
                .toString(new java.util.HashMap<String, Object>() {{
                    put("username", username);
                }});
    }
}
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

import freemarker.template.Configuration;
import freemarker.template.TemplateException;
import freemarker.template.Version;

import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

public class HelloWorldApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> hello(request));
    }

    private static String hello(Request request) throws Exception {
        Configuration cfg = new Configuration(new Version("2.3.30"));
        cfg.setDirectoryForTemplateLoading(new java.io.File("templates"));

        Map<String, Object> dataModel = new HashMap<>();
        dataModel.put("username", request.params(":username"));

        StringWriter out = new StringWriter();
        cfg.getTemplate("hello.html").process(dataModel, out);

        return out.toString();
    }
}
