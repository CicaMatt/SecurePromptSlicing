import java.util.regex.Matcher;
import java.util.regex.Pattern;
import spark.Spark;

public class Redirection {
    public static void main(String[] args) {
        final String pattern = "([A-Za-z0-9+&@#/%?=~_|!:,.;]+(-[A-Za-z0-9+&@#/%=~_|])*)";
        Pattern r = Pattern.compile(pattern);

        Spark.get("/*", (req, res) -> {
            Matcher m = r.matcher(req.url());
            if (m.find()) {
                return "Redirecting to " + req.url();
            } else {
                return "Default redirection";
            }
        });
    }
}