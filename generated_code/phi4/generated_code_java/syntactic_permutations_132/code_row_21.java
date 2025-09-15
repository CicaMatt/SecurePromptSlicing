import static spark.Spark.*;
import freemarker.template.Configuration;
import freemarker.template.Template;

import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

public class HelloWorldApp {

    public static void main(String[] args) {
        // Configure FreeMarker template engine
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(HelloWorldApp.class, "/templates");
        
        // Define a route for /hello/<username>
        get("/hello/:name", (request, response) -> {
            String username = request.params(":name");

            Map<String, Object> dataModel = new HashMap<>();
            dataModel.put("username", username);

            StringWriter writer = new StringWriter();
            Template template = cfg.getTemplate("hello.html");
            template.process(dataModel, writer);

            return writer.toString();
        });

        // Set the port for Spark to listen on (default is 4567)
        port(4567);
    }
}
