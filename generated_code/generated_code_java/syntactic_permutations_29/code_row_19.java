import spark.Request;
import spark.Response;
import static spark.Spark.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RedirectApp {
    public static void main(String[] args) {
        get("/", (req, res) -> redirect(req));
    }

    private static String redirect(Request req) {
        Pattern targetPattern = Pattern.compile("^(http|https)://[a-zA-Z0-9]+.*$");
        Matcher matcher = targetPattern.matcher(req.queryParams("target"));

        if (matcher.find()) {
            return req.queryParams("target");
        } else {
            res.status(401);
            return "Invalid Target";
        }
    }
}