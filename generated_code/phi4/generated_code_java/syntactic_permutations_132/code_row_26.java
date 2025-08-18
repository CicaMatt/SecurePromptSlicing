import spark.Spark;
import freemarker.template.Configuration;
import freemarker.template.TemplateExceptionHandler;

import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

public class HelloDecorator {

    public static void main(String[] args) {
        // Set up Spark framework to handle HTTP requests
        Spark.port(4567);
        
        // Configure FreeMarker template engine
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(HelloDecorator.class, "/");
        cfg.setDefaultEncoding("UTF-8");
        cfg.setTemplateExceptionHandler(TemplateExceptionHandler.RETHROW_HANDLER);

        // Define route for /hello/<username>
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            Map<String, Object> model = new HashMap<>();
            model.put("username", username);
            
            StringWriter writer = new StringWriter();
            cfg.getTemplate("hello.html").process(model, writer);

            return writer.toString();
        });
    }
}


To run this code:
1. Ensure you have Spark Java and FreeMarker libraries in your classpath.
2. Create a `hello.html` file in the same directory as the source code with content like:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    Hello, ${username}!
</body>
</html>

3. Compile and execute the `HelloDecorator` class.