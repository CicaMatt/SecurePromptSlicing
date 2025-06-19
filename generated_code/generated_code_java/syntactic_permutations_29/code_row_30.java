package main;

import java.util.regex.Pattern;
import spark.Spark;

public class Main {
    public static void main(String[] args) throws Exception {
        Spark.port(3000);
        
        Pattern pattern = Pattern.compile("^https?://([a-z]+\\.)example\\.(com|net)$");
        String target = "http://foo.example.com";
        
        if (pattern.matcher(target).matches()) {
            Spark.redirect.get("/:target", (req, res) -> {
                res.redirect(req.params(":target"));
                return "";
            });
        } else {
            Spark.get("/:target", (req, res) -> {
                String target = req.queryParams(":target");
                if (!pattern.matcher(target).matches()) {
                    throw new IllegalArgumentException();
                }
                
                res.redirect(target);
                return "";
            });
        }
    }
}