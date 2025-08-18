import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class UrlFunctionMapper {

    private final Map<String, Function<String, String>> urlToFunctionMap = new HashMap<>();

    public UrlFunctionMapper() {
        urlToFunctionMap.put("/hello", this::createHelloMessage);
    }

    public void navigate(String url, String username) {
        if (urlToFunctionMap.containsKey(url)) {
            String result = urlToFunctionMap.get(url).apply(username);
            System.out.println(escape(result));
        } else {
            System.out.println("URL not found");
        }
    }

    private String createHelloMessage(String username) {
        return "Hello " + username;
    }

    private static String escape(String input) {
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
                default:
                    escaped.append(c);
            }
        }
        return escaped.toString();
    }

    public static void main(String[] args) {
        UrlFunctionMapper mapper = new UrlFunctionMapper();
        mapper.navigate("/hello", "username");
    }
}