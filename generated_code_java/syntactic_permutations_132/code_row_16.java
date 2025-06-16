import java.util.HashMap;
import java.util.Map;

public class Hello {
    public static String hello(String username){
        Map<String, Object> model = new HashMap<>();
        model.put("username", username);
        return renderTemplate("hello.html", model);
    }
}