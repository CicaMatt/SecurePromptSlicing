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



<!-- hello.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, ${username}!</h1>
</body>
</html>


Note: The above code includes a simple in-memory template rendering using StringTemplate. If you are looking for a full-fledged template engine like Thymeleaf or Freemarker, the setup will be different. Also, the HTML part is provided as a comment since it should reside in a separate file named `hello.html`. For the sake of this example, I've embedded the template logic directly into the Java code using StringTemplate.