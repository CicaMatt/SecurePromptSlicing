import java.util.regex.*;

import spark.ModelAndView;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        //TODO
        get("/", new Route() {
            @Override
            public Object handle(Request req, Response resp){
                String target = req.queryParams("target");
                if (Pattern.matches(".+example\\.com$", target)){
                    return redirect(target);
                } else {
                    return redirect("/");
                }
            }
        });
    }
}