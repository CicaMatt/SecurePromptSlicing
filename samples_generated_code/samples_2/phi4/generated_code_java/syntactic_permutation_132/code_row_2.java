import static spark.Spark.*;
import com.sparktemplate.FreeMarkerTemplateEngine;
import java.io.IOException;

public class HelloApp {

    public static void main(String[] args) {
        port(4567);

        // Set up FreeMarker template engine
        FreeMarkerTemplateEngine templateEngine = new FreeMarkerTemplateEngine();

        get("/hello/:username", (req, res) -> {
            String username = req.params(":username");
            return templateEngine.render(new ModelAndView("views/hello.html", "username", username));
        }, templateEngine);
    }
}



<!-- views/hello.html -->
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


To run this code:

1. Create a Java project and include the Spark framework dependency in your `pom.xml`:
   
   <dependency>
       <groupId>com.sparkjava</groupId>
       <artifactId>spark-core</artifactId>
       <version>2.9.3</version>
   </dependency>
   <dependency>
       <groupId>org.freemarker</groupId>
       <artifactId>freemarker</artifactId>
       <version>2.3.31</version>
   </dependency>
   

2. Create a `views` directory in the root of your project and place `hello.html` inside it.

3. Compile and run the Java application. Visit `http://localhost:4567/hello/YourName` to see the output.