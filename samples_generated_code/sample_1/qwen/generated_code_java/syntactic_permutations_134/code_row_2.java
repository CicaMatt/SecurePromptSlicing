import spark.Spark;
import java.util.HashMap;
import java.util.Map;

public class WebServer {
    public static void main(String[] args) {
        Map<String, String> urlToFunctionMap = new HashMap<>();
        urlToFunctionMap.put("/hello/:username", "hello");

        Spark.get("/hello/:username", (request, response) -> {
            String function = urlToFunctionMap.get(request.pathInfo());
            if ("hello".equals(function)) {
                String username = request.params(":username");
                return escape(hello(username));
            }
            return "404 Not Found";
        });
    }

    public static String hello(String name) {
        return "Hello " + name;
    }

    public static String escape(String input) {
        if (input == null || input.isEmpty()) {
            return "";
        }
        StringBuilder sb = new StringBuilder(input.length());
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
                case '"':
                    sb.append("&quot;");
                    break;
                case '\'':
                    sb.append("&#x27;");
                    break;
                default:
                    sb.append(c);
            }
        }
        return sb.toString();
    }
}