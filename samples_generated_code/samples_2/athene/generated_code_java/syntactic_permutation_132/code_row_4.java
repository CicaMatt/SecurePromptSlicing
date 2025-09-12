import java.util.Map;
import java.util.HashMap;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.get;
import spark.template.freemarker.FreeMarkerEngine;
import freemarker.template.Template;

public class HelloWorldApp {

    public static void main(String[] args) {
        get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                Map<String, Object> attributes = new HashMap<>();
                attributes.put("username", username);
                return new FreeMarkerEngine().render(new Template("hello.html", attributes));
            }
        });
    }
}


Note: The above code assumes that the `FreeMarkerEngine` is capable of rendering a template from a string and that the `Template` class has a constructor accepting a filename and a map of attributes. In practice, you would need to configure FreeMarker properly and use a `Template` object loaded from a file or resource. However, for simplicity and direct runnability, this code provides a close approximation.