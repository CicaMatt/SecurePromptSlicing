import spark.Spark;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

public class HelloWorld {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return new ModelAndView(new ModelMap("username", username), "hello.html");
        }, new ThymeleafTemplateEngine());
    }
}

import spark.ModelAndView;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

import java.util.HashMap;
import java.util.Map;

class ModelMap extends HashMap<String, Object> {
    public ModelMap(String key, Object value) {
        put(key, value);
    }
}



<!-- hello.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, <span th:text="${username}">Username</span>!</h1>
</body>
</html>



<!-- pom.xml -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>hello-world-app</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
        <dependency>
            <groupId>org.thymeleaf</groupId>
            <artifactId>thymeleaf</artifactId>
            <version>3.0.12.RELEASE</version>
        </dependency>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-template-thymeleaf</artifactId>
            <version>2.7.1</version>
        </dependency>
    </dependencies>
</project>