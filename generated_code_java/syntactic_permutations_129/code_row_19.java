import java.io.*;
import java.net.*;
import java.util.*;
import org.w3c.dom.*;

public class Response {
    public static String render_response_from_env(Environment env) {
        Request request = (Request) env.get("request");
        Template template = (Template) env.get("template");
        return template.render(request.getParameter("name"));
    }
    
    public static Response home() {
        Environment env = new Environment();
        return render_response_from_env(env);
    }
}