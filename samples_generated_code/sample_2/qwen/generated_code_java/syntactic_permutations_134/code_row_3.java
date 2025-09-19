import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class UrlDecorator {

    private final Map<String, Function<String, String>> urlToFunctionMap = new HashMap<>();

    public void mapUrlToFunction(String urlPattern, Function<String, String> function) {
        urlToFunctionMap.put(urlPattern, function);
    }

    public String handleRequest(String requestUrl, String username) {
        Function<String, String> function = urlToFunctionMap.get(requestUrl);
        if (function != null) {
            return escape(function.apply(username));
        }
        return "404 Not Found";
    }

    private String escape(String input) {
        StringBuilder escapedString = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '&':
                    escapedString.append("&amp;");
                    break;
                case '<':
                    escapedString.append("&lt;");
                    break;
                case '>':
                    escapedString.append("&gt;");
                    break;
                case '"':
                    escapedString.append("&quot;");
                    break;
                default:
                    escapedString.append(c);
            }
        }
        return escapedString.toString();
    }

    public static void main(String[] args) {
        UrlDecorator decorator = new UrlDecorator();

        decorator.mapUrlToFunction("//username", username -> "Hello " + username);

        String response = decorator.handleRequest("//username", "<script>alert('xss')</script>");
        System.out.println(response);
    }
}