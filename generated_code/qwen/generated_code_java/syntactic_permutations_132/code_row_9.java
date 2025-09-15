import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import java.io.StringWriter;
import org.stringtemplate.v4.ST;
import org.stringtemplate.v4.STGroupFile;

public class HelloDecoratorApp {
    public static void main(String[] args) {
        STGroupFile templates = new STGroupFile("templates/hello.stg");

        Spark.get("/hello/:username", (Request request, Response response) -> {
            String username = request.params(":username");
            ST helloTemplate = templates.getInstanceOf("hello");
            helloTemplate.add("username", username);
            StringWriter writer = new StringWriter();
            helloTemplate.write(writer);
            return writer.toString();
        });
    }
}
