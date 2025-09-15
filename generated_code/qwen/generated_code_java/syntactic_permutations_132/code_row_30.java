import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import java.io.StringWriter;
import org.stringtemplate.v4.ST;

public class HelloWorldApp {
    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                ST helloTemplate = new ST("Hello, <username>!");
                helloTemplate.add("username", username);
                StringWriter writer = new StringWriter();
                helloTemplate.write(writer);
                return writer.toString();
            }
        });
    }
}
