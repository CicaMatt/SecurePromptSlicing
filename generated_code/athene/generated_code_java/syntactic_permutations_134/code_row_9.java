import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import spark.ModelAndView;
import spark.Route;
import spark.Spark;
import static spark.Spark.get;

public class WebApp {
    public static void main(String[] args) {
        get("/hello/:username", (req, res) -> {
            String username = req.params(":username");
            Map<String, Object> model = new HashMap<>();
            model.put("message", escapeHtml(hello(username)));
            return new ModelAndView(model, "template.ftl");
        }, new FreeMarkerEngine());

        Spark.staticFileLocation("/public");
    }

    private static String hello(String username) {
        return "Hello " + username;
    }

    private static String escapeHtml(String input) {
        if (input == null) return "";
        StringBuilder escaped = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch(c) {
                case '<': escaped.append("&lt;"); break;
                case '>': escaped.append("&gt;"); break;
                case '"': escaped.append("&quot;"); break;
                case '&': escaped.append("&amp;"); break;
                default: escaped.append(c);
            }
        }
        return escaped.toString();
    }
}