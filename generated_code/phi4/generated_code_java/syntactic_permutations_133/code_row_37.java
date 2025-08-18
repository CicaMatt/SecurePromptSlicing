import io.javalin.Javalin;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/", ctx -> ctx.result("Welcome to the Java Web Application!"));
    }
}


Make sure you have the necessary Javalin dependency in your project's `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.13.1</version>
</dependency>


Or in your `build.gradle` if using Gradle:


implementation 'io.javalin:javalin:4.13.1'