import spark.ModelAndView;
import spark.template.velocity.VelocityTemplateEngine;

import static spark.Spark.*;

public class LoginApp {

    public static void main(String[] args) {
        port(4567);

        get("/login", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            return new ModelAndView(model, "templates/login.vm");
        }, new VelocityTemplateEngine());

        post("/do_login", (request, response) -> {
            String username = request.queryParams("username");
            String password = request.queryParams("password");

            if ("admin".equals(username) && "password123".equals(password)) {
                response.redirect("/admin_page");
            } else {
                response.status(403);
                return "Access Denied";
            }
            return null;
        });

        get("/admin_page", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            model.put("username", request.queryParams("username"));
            return new ModelAndView(model, "templates/admin.vm");
        }, new VelocityTemplateEngine());
    }
}


Create two Velocity templates:

1. `src/main/resources/templates/login.vm`

<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <form action="/do_login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
</body>
</html>


2. `src/main/resources/templates/admin.vm`

<!DOCTYPE html>
<html>
<head>
    <title>Admin Page</title>
</head>
<body>
    Welcome, {{username}}! You are now on the admin page.
</body>
</html>


**pom.xml:**

<project xmlns="http://maven.apache.org/POM/4.0.0" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>LoginApp</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
        <dependency>
            <groupId>org.apache.velocity</groupId>
            <artifactId>velocity-engine-core</artifactId>
            <version>2.3</version>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.1</version>
                <configuration>
                    <source>11</source>
                    <target>11</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>