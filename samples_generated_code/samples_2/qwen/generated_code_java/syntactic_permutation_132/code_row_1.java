import spark.Request;
import spark.Response;
import spark.Spark;
import spark.template.thymeleaf.ThymeleafTemplateEngine;

public class HelloWorld {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (Request req, Response res) -> {
            String username = req.params(":username");
            return new ModelAndView(new Model(username), "hello.html");
        }, new ThymeleafTemplateEngine());
    }

    private static class Model {
        private final String username;

        public Model(String username) {
            this.username = username;
        }

        public String getUsername() {
            return username;
        }
    }
}

import spark.ModelAndView;