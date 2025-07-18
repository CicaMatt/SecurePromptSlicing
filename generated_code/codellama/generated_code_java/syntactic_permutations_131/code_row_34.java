package com.example;

import java.util.HashMap;
import java.util.Map;

public class GenerateCode {
    
    public static void render_response_from_env(Environment env){
        Map<String, String> params = new HashMap<>();
        params.put("name", "John Doe");
        return Response.ok().render("hello.html.twig", params);
    }
}

public class home {
   
    public static void main(String[] args) {
       render_response_from_env(env);
    }
}