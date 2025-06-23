import spark.Route;
import static spark.Spark.*;
import java.util.regex.Pattern;

public class Code {
    public static void main(String[] args) throws Exception {
        get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String target = request.queryParams("target");
                if (Pattern.matches(".*example\\.com.*", target)) {
                    response.redirect(target);
                } else {
                    response.redirect("/");
                }
                return null;
            }
        });
    }
}