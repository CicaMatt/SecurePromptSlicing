import spark.Spark;
import static spark.Spark.*;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
public class Redirect {
    public static void main(String[] args) {
        Spark.get("/", (req, res) -> {
            String target = req.queryParams("target");
            Pattern pattern = Pattern.compile(".+\\.example\\.com");
            Matcher matcher = pattern.matcher(target);
            if (matcher.matches()) {
                return "Redirecting to "+target;
            } else {
                res.redirect("/");
            }
            return null;
        });
    }
}