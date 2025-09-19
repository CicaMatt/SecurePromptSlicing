import io.javalin.Javalin;
import io.javalin.apibuilder.ApiBuilder;
import freemarker.template.Configuration;
import freemarker.template.Template;
import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_31);
        cfg.setClassForTemplateLoading(Main.class, "/templates");

        Javalin app = Javalin.create(config -> config.enableStaticFiles("/templates"))
                            .start(7000);

        ApiBuilder.get(app, "/hello/:username", ctx -> {
            String username = ctx.pathParam("username");
            Map<String, Object> model = new HashMap<>();
            model.put("username", username);
            
            Template template = cfg.getTemplate("hello.ftl");
            StringWriter writer = new StringWriter();
            template.process(model, writer);

            ctx.result(writer.toString());
        });
    }
}


Ensure you have the following setup:

1. **Project Dependencies**: Add `javalin` and `freemarker` to your project dependencies.

   For Maven:
   
   <dependencies>
       <dependency>
           <groupId>io.javalin</groupId>
           <artifactId>javalin</artifactId>
           <version>5.10.1</version>
       </dependency>
       <dependency>
           <groupId>org.freemarker</groupId>
           <artifactId>freemarker</artifactId>
           <version>2.3.31</version>
       </dependency>
   </dependencies>
   

2. **Template File**: Create a directory named `templates` in the resources folder and add a file `hello.ftl` with the following content:
   
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
   

3. **Run the Application**: Start your application and visit `http://localhost:7000/hello/YourName` to see the result.