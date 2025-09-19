import io.javalin.Javalin;
import spark.template.handlebars.HandlebarsTemplateEngine;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.staticFiles.enableWebJars()).start(7000);

        app.get("/info", ctx -> {
            String username = "JohnDoe"; // Example username
            String email = "john.doe@example.com"; // Example email
            String ssnLastFour = "1234"; // Example last 4 digits of SSN

            // Render the information using Handlebars template engine
            String html = new HandlebarsTemplateEngine().render(
                "templates/info.mustache",
                Map.of(
                    "username", username,
                    "email", email,
                    "ssnLastFour", ssnLastFour
                )
            );

            ctx.html(html);
        });
    }
}



<!-- File: src/main/resources/templates/info.mustache -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>User Information</title>
    <link rel="stylesheet" href="/webjars/bootstrap/4.5.2/css/bootstrap.min.css">
</head>
<body class="container">
    <h1>User Information</h1>
    <div class="card mt-3">
        <div class="card-body">
            <p><strong>Username:</strong> {{username}}</p>
            <p><strong>Email:</strong> {{email}}</p>
            <p><strong>Last 4 Digits of SSN:</strong> ****{{ssnLastFour}}</p>
        </div>
    </div>

    <script src="/webjars/jquery/3.5.1/jquery.min.js"></script>
    <script src="/webjars/bootstrap/4.5.2/js/bootstrap.bundle.min.js"></script>
</body>
</html>


Ensure you have the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <!-- Javalin Web Framework -->
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.1.0</version>
    </dependency>

    <!-- Handlebars Template Engine -->
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-template-handlebars</artifactId>
        <version>2.7.1</version>
    </dependency>

    <!-- WebJars for Bootstrap and jQuery -->
    <dependency>
        <groupId>org.webjars</groupId>
        <artifactId>bootstrap</artifactId>
        <version>4.5.2</version>
    </dependency>
    <dependency>
        <groupId>org.webjars</groupId>
        <artifactId>jquery</artifactId>
        <version>3.5.1</version>
    </dependency>

    <!-- JUnit for testing (optional) -->
    <dependency>
        <groupId>junit</groupId>
        <artifactId>junit</artifactId>
        <version>4.13.2</version>
        <scope>test</scope>
    </dependency>
</dependencies>


This setup uses Javalin as the web framework, Handlebars for templating, and WebJars for Bootstrap and jQuery.