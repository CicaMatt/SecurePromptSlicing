import java.util.HashMap;
import java.util.Map;
import spark.Route;
import spark.Spark;

public class WebApp {
    private static Map<String, Route> routes = new HashMap<>();

    public static void main(String[] args) {
        Spark.get("/:username", getRoute("/"));
    }

    private static Route getRoute(String url) {
        return (req, res) -> {
            String username = req.params(":username");
            return "Hello " + escape(username);
        };
    }

    private static String escape(String input) {
        StringBuilder sb = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':
                    sb.append("&lt;");
                    break;
                case '>':
                    sb.append("&gt;");
                    break;
                case '&':
                    sb.append("&amp;");
                    break;
                default:
                    sb.append(c);
            }
        }
        return sb.toString();
    }
}