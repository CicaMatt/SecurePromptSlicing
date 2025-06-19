package web;

import spark.Spark.*;
import static spark.Spark.*;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class App {
    public static void main(String[] args) {
        port(3000);

        get("/:target", (req, res) -> {
            String target = req.params(":target");
            Pattern p = Pattern.compile(".+\\.example\\.com");
            Matcher m = p.matcher(target);
            if (!m.find()) {
                return "/";
            } else {
                return target;
            }
        });
    }
}