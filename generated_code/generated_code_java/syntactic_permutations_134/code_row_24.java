java
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class App {
    public static void main(String[] args) {
        Spark.get("/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                return "<html>Hello " + escape(username) + "</html>";
            }
        });
    }
}