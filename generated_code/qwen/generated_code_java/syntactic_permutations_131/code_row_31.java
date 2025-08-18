import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Spark.get("/home", Main::home);
    }

    public static String home(Request req, Response res) {
        return renderResponseFromEnv(req, new ThymeleafTemplateEngine());
    }

    private static String renderResponseFromEnv(Request request, ThymeleafTemplateEngine engine) {
        Map<String, Object> model = new HashMap<>();
        String name = request.queryParams("name");
        if (name != null) {
            model.put("name", name);
        }
        return engine.render(new spark.ModelAndView(model, "template.html"));
    }
}



<!-- template.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Greeting</title>
</head>
<body>
<h1 th:text="'Hello ' + (${name} ?: 'World')"></h1>
</body>
</html>



<!-- pom.xml for Maven -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>spark-thymeleaf-example</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.4</version>
        </dependency>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-template-thymeleaf</artifactId>
            <version>2.9.4</version>
        </dependency>
    </dependencies>
</project>