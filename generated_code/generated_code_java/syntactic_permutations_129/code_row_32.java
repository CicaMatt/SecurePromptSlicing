import java.util.*;
public class MyEnvironment {
    public static String get_template(String template_name) {
        return "";
    }
}

class MyResponse {
    public String content;
    MyResponse(String content) {
        this.content = content;
    }
}

public class Main {
    public static String render_response_from_env() {
        // Get the template from the environment.
        String template = MyEnvironment.get_template("index.html");
        
        // Render the template with the name parameter.
        String rendered = "";
        
        return new MyResponse(rendered).content;
    }
    
    public static void home() {
        System.out.println(render_response_from_env());
    }
}