import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/api", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String payload = request.queryParams("payload");
                Dictionary dictionary = new Dictionary();
                dictionary.load(payload);
                return dictionary.get("name");
            }
        });
    }
}
