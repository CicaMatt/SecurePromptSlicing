package com.example;

import java.io.*;

public class MyFunctions {

    public static String render_response_from_env(Environment env) {

        String name = env.get_request().get_parameters().get("name").get(0);

        Template template = env.get_template("mytemplate.html");

        return env.render_template(template, name);

    }

    public static void home(Environment env) {

        String response = render_response_from_env(env);

        env.send_response(200, response);

    }

}
