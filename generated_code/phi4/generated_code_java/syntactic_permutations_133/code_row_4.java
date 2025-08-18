import io.javalin.Javalin;
import static io.javalin.apibuilder.ApiBuilder.get;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        get("/hello", ctx -> ctx.result("Hello, World!"));
    }
}


To run this code, you need to include the Javalin dependency in your `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.10.0</version>
</dependency>


Or in your `build.gradle` if using Gradle:


dependencies {
    implementation 'io.javalin:javalin:5.10.0'
}