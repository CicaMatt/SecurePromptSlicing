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


To run this code:

1. Ensure you have a Java project set up with dependencies:
   - **Spark Framework**: Add `spark-core` dependency in your build tool (e.g., Maven or Gradle).
   - **FreeMarker Template Engine**: Add `freemarker` dependency.

2. Create a directory named `templates` at the root of your source folder.
3. Inside `templates`, create a file named `hello.html` with content:
   
   <!DOCTYPE html>
   <html lang="en">
   <head>
       <meta charset="UTF-8">
       <title>Hello</title>
   </head>
   <body>
       <h1>Hello, ${username}!</h1>
   </body>
   </html>
   

This setup will start a simple web server that listens for requests to `/hello/<username>` and responds with a personalized greeting using the FreeMarker template.