import java.util.regex.Pattern;
import spark.Request;
import static spark.Spark.*;
public class Redirect {
    public static void main(String[] args) {
        Pattern pattern = Pattern.compile(".*example\\.com.*");
        get("/", (req, res) -> {
            String target = req.queryParams("target");
            if (pattern.matcher(target).matches()) {
                return "Redirecting to: "+target;
            } else {
                return "Redirecting to /";
            }
        });
    }
}