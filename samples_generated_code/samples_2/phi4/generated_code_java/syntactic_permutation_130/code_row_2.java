import java.util.Map;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/", (request, response) -> home(request, response));
    }

    public static String renderResponseFromEnv(Map<String, Object> env, Map<String, String[]> requestParams) {
        String name = requestParams.get("name")[0];
        String template = (String) env.getOrDefault("template", "Hello, %s!");
        return String.format(template, name);
    }

    public static String home(spark.Request request, spark.Response response) {
        Map<String, Object> env = System.getenv();
        return renderResponseFromEnv(env, request.queryParams());
    }
}


Make sure to include the Spark Java library in your project dependencies. For Maven, you can add:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>