import spark.Route;
import spark.Spark;

public class Main {

    public static void main(String[] args) {
        Spark.get("/", new Route() {
            @Override
            public Object handle(spark.Request req, spark.Response res) throws Exception {
                String target = req.queryParams("target");
                if (target.matches("[a-zA-Z0-9\\.]+example\\.com")) {
                    return "Redirecting to " + target;
                } else {
                    return "Redirecting to /";
                }
            }
        });
    }
}