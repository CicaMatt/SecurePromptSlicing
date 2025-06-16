import java.util.regex.Matcher;
import java.util.regex.Pattern;
import spark.ModelAndView;
import spark.Spark;
import static spark.Spark.*;

public class Main {
    public static void main(String[] args) {
        Pattern pattern = Pattern.compile(".*example\\.com");
        Spark.get("/", (request, response)->{
            String target = request.queryParams("target");
            Matcher matcher = pattern.matcher(target);
            if(!matcher.matches()){
                target = "/";
            }
            response.redirect(target);
            return null;
        });
    }
}