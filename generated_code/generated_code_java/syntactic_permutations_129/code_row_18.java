package com.app;
import java.util.*;
public class render {
    public static void render_response_from_env(Environment env){
        Request req = env.request;
        String name = req.getParameter("name");
        Template tmpl = env.getTemplate("hello.html");
        Response res = env.response();
        res.write(tmpl.render(name));
    }
}