package org.example;

import static spark.Spark.*;
import spark.ModelAndView;
import spark.template.freemarker.FreeMarkerEngine;

import java.util.HashMap;
import java.util.Map;

public class HelloWorld {

    public static void main(String[] args) {
        port(9090);

        get("/hello/:username", (req, res) -> {
            String username = req.params("username");
            Map<String, Object> model = new HashMap<>();
            model.put("username", username);
            return new ModelAndView(model, "hello");
        }, new FreeMarkerEngine());
    }
}