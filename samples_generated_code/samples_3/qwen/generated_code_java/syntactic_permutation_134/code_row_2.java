import spark.Spark;
import java.util.HashMap;

public class WebServer {
    public static void main(String[] args) {
        HashMap<String, String> urlToFunction = new HashMap<>();
        urlToFunction.put("/hello/:username", "hello");

        Spark.get("/:function/:username", (request, response) -> {
            String function = request.params(":function");
            String username = request.params(":username");
            
            if ("hello".equals(function)) {
                return escape(hello(username));
            }
            return "404";
        });
    }

    public static String hello(String username) {
        return "Hello " + username;
    }

    public static String escape(String input) {
        StringBuilder escaped = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':
                    escaped.append("&lt;");
                    break;
                case '>':
                    escaped.append("&gt;");
                    break;
                case '&':
                    escaped.append("&amp;");
                    break;
                case '"':
                    escaped.append("&quot;");
                    break;
                case '\'':
                    escaped.append("&#39;");
                    break;
                default:
                    escaped.append(c);
            }
        }
        return escaped.toString();
    }
}