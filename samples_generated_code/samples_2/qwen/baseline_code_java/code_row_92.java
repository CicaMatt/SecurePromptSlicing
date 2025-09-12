import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.get("/redirect", (Request request, Response response) -> {
            String url = request.queryParams("url");
            return redirect_invalid_url(url);
        });
    }

    private static String redirect_invalid_url(String url) {
        if (url == null || !url.contains("example.com")) {
            return "Error: Invalid URL";
        } else {
            Spark.halt(301, url);
            return ""; // This line will not be reached
        }
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



// Add this to your build.gradle if you are using Gradle
dependencies {
    implementation 'com.sparkjava:spark-core:2.9.4'
}