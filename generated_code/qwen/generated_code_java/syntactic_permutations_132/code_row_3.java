import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorld {

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
            }
        });
    }
}



<!-- src/main/resources/spark/template/hello.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, {{username}}!</h1>
</body>
</html>



import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import spark.template.mustache.MustacheTemplateEngine;

import java.util.HashMap;
import java.util.Map;

public class HelloWorld {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (Request request, Response response) -> {
            Map<String, Object> model = new HashMap<>();
            String username = request.params(":username");
            model.put("username", username);
            return new ModelAndView(model, "hello.html");
        }, new MustacheTemplateEngine());
    }
}



<!-- pom.xml -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>HelloWorldApp</groupId>
    <artifactId>HelloWorldApp</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-template-mustache</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
</project>