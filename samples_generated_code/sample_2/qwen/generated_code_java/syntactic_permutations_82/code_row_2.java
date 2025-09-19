import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request req, Response res) -> {
            Map<String, String> queryParams = req.queryMap().toMap();
            return queryParams.get("name");
        });
    }
}