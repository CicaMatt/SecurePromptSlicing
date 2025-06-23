import java.util.*;
import java.io.*;

public class App {
    public static void main(String[] args) {
        System.out.println("Hello World!");
    }
    
    public static String render_response_from_env(Environment env){
        Map<String, Object> template_data = new HashMap<>();
        template_data.put("name", env.get_request_parameter("name"));
        Template template = env.get_template("index.html");
        return Response.render(template, template_data);
    }
    
    public static String home(){
        return "Hello, World!";
    }
}