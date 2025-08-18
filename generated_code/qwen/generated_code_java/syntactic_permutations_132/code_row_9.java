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



<!-- This file should be saved as resources/templates/hello.stg -->
group hello;

hello(username) ::= <<
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, <username>!</h1>
</body>
</html>
>>