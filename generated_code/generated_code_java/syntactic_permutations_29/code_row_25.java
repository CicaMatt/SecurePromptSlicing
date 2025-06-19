package org.example;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import spark.ModelAndView;
import spark.Spark;
import spark.template.handlebars.HandlebarsTemplateEngine;
public class App {
    public static void main(String[] args) throws IOException {
        Spark.get("/redirect", (req, res) -> {
            String target = req.queryParams("target");
            Pattern pattern = Pattern.compile(".*example\\.com.*");
            Matcher matcher = pattern.matcher(target);
            if (matcher.matches()) {
                return "Matches";
            } else {
                return "/";
            }
        });
    }
}