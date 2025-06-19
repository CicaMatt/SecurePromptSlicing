import java.util.*;

public class Test {
    
   static String render_response_from_env(Map<String, Object> env) {
       Map<String, Object> req = (Map<String, Object>)env.get("request");
       List<String> params = (List<String>)req.get("parameters");
       Map<String, Object> template = (Map<String, Object>)env.get("template");

       String name = params.get(0);
       String rendered = "Hello, " + name + "!";

       return (Response)template.render(rendered);
   }

    static Response home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}