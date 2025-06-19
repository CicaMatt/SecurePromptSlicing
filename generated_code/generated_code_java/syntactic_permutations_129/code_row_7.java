import java.util.HashMap;
import java.util.Map;

public class HelloWorld {
    public String render_response_from_env(String name, Map<String, Object> env) {
        return env.get("template").toString().replace("NAME", name);
    }
    
    public String home() {
        Map<String, Object> env = new HashMap<String, Object>();
        env.put("template", "Hello, NAME!");
        
        return render_response_from_env("John Doe", env);
    }
}