import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import spark.ModelAndView;
import spark.Route;
import spark.Spark;
import static spark.Spark.get;

public class App {
    public static void main(String[] args) {
        get("/hello/:username", (req, res) -> {
            String username = req.params(":username");
            Map<String, Object> model = new HashMap<>();
            model.put("message", escape(hello(username)));
            return new ModelAndView(model, "template.ftl");
        }, new FreeMarkerEngine());

        Spark.init();
    }

    public static String hello(String username) {
        return "Hello " + username;
    }

    public static String escape(String input) {
        if (input == null) return null;
        StringBuilder result = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':
                    result.append("&lt;");
                    break;
                case '>':
                    result.append("&gt;");
                    break;
                case '&':
                    result.append("&amp;");
                    break;
                case '"':
                    result.append("&quot;");
                    break;
                case '\'':
                    result.append("&#39;");
                    break;
                default:
                    result.append(c);
            }
        }
        return result.toString();
    }
}