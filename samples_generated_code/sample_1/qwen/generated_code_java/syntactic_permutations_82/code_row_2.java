import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request request, Response response) -> {
            Map<String, String> queryParams = request.queryMap().toMap();
            return queryParams.getOrDefault("name", "Name not provided");
        });
    }
}