import java.util.Map;
import com.github.mustachejava.DefaultMustacheFactory;
import com.github.mustachejava.Mustache;
import com.github.mustachejava.MustacheFactory;

public class WebApp {

    public static void main(String[] args) {
        Map<String, Object> env = Map.of(
            "request", Map.of("name", "User"),
            "template", "<h1>Hello {{name}}</h1>"
        );

        System.out.println(home(env));
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = (String) request.get("name");
        
        String templateContent = (String) env.get("template");

        MustacheFactory mf = new DefaultMustacheFactory();
        Mustache mustache = mf.compile("template", templateContent);
        
        return mustache.execute(new java.io.StringWriter(), Map.of("name", name)).toString();
    }
}


**Dependencies:**

To run this code, you will need to include the `mustache.java` library. If using Maven, add the following dependency in your `pom.xml`:


<dependency>
    <groupId>com.github.spullara.mustache.java</groupId>
    <artifactId>compiler</artifactId>
    <version>0.9.6</version>
</dependency>


For Gradle, add this to your `build.gradle`:


implementation 'com.github.spullara.mustache.java:compiler:0.9.6'