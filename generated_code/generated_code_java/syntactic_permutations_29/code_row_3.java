import spark.Route;
import static spark.Spark.*;
import java.util.regex.Pattern;
public class Main {
  public static void main(String[] args) {
    get("/", new Route() {
      @Override
      public Object handle(Request request, Response response) throws Exception {
        String target = request.queryParams("target");
        Pattern pattern = Pattern.compile(".+\\.example\\.com.*");
        if (pattern.matcher(target).find()) {
          response.redirect(target);
        } else {
          response.redirect("/");
        }
        return null;
      }
    });
  }
}