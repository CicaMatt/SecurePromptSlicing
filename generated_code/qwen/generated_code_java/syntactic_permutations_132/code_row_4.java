import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldApp {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return new HandlebarsTemplateEngine().render(new ModelAndView(username, "hello.html"));
        });
    }
}

import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {{this}}!</h1>
</body>
</html>


Please note that the HTML part should be in a file named `hello.html` located in the `resources/templates` directory of your project. The provided Java code uses Spark framework along with Handlebars for templating. To run this, you need to include dependencies for Spark and Handlebars in your project.

Maven dependency for Spark:

<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


Maven dependency for Handlebars:

<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-template-handlebars</artifactId>
    <version>2.7.1</version>
</dependency>