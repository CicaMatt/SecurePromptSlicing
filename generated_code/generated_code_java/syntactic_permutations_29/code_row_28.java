import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;
import java.util.regex.Pattern;
public class Redirect{
    private static final Pattern PATTERN = Pattern.compile(".*example\\.com");
    public static void main(String[] args) {
        get("/", new Route() {
            @Override
            public Object handle(Request request, Response response){
                String target = request.queryParams("target");
                if (PATTERN.matcher(target).matches()) {
                    response.redirect(target);
                } else {
                    response.redirect("/");
                }
                return null;
            }
        });
    }
}