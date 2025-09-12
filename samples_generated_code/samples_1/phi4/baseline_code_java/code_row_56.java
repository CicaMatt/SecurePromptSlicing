import io.javalin.Javalin;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/", ctx -> {
            return "Hello, World!";
        });
    }
}


To run this code, you need to include the Javalin dependency in your project. If you are using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.0.1</version>
</dependency>


If you're using Gradle, add this line to your `build.gradle`:


implementation 'io.javalin:javalin:5.0.1'