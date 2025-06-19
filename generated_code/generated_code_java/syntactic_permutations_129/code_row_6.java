import java.io.*;

public class Main {
    public static String render_response_from_env(String name) {
        return new Environment().getTemplate("hello.html").render(new ModelMap().addAttribute("name", name));
    }
    
    public static Response home() {
        return new Response(Response.OK).body(render_response_from_env("John"));
    }
    
}