import spark.Spark;
import static spark.Spark.*;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
public class Main {
    public static void main(String[] args) {
        get("/", (req, res) -> {
            String target = req.queryParams("target");
            Pattern p = Pattern.compile("https?://(.*\\.)*example.com/");
            Matcher m = p.matcher(target);
            if (!m.matches()) {
                return "Invalid URL!";
            } else {
                res.redirect(target);
            }
        });
    }
}