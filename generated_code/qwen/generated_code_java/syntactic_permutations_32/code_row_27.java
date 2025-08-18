import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class RedirectApp {

    public static void main(String[] args) {
        Spark.get("/redirect/:url", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String url = request.params(":url");
                return redirectInvalidUrl(url);
            }
        });
    }

    private static Object redirectInvalidUrl(String url) {
        if (url != null && url.contains("example.com")) {
            Spark.redirect(url);
        }
        return ".";
    }
}



<!-- Add this to your pom.xml if you are using Maven -->
<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.4</version>
    </dependency>
</dependencies>