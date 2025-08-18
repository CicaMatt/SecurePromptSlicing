import io.javalin.Javalin;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/hello", ctx -> ctx.result("Hello, World!"));
    }
}


To run this code, you will need to include the Javalin dependency in your project. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.9.1</version>
</dependency>


For Gradle, add this line to your `build.gradle`:


implementation 'io.javalin:javalin:5.9.1'