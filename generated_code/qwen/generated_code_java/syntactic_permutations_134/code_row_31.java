import java.util.HashMap;
import java.util.Map;

public class DecoratorExample {
    private Map<String, Function<String, String>> urlFunctionMap = new HashMap<>();

    public DecoratorExample() {
        mapUrlToFunction("/hello", this::hello);
    }

    private void mapUrlToFunction(String url, Function<String, String> function) {
        urlFunctionMap.put(url, function);
    }

    public String callFunction(String url, String argument) {
        if (urlFunctionMap.containsKey(url)) {
            return urlFunctionMap.get(url).apply(argument);
        }
        return "URL not found";
    }

    private String hello(String username) {
        return "Hello " + escape(username);
    }

    private String escape(String input) {
        if (input == null) {
            return "";
        }
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
                case '"':
                    sb.append("&quot;");
                    break;
                default:
                    sb.append(c);
            }
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        DecoratorExample example = new DecoratorExample();
        String result = example.callFunction("/hello", "User&Name");
        System.out.println(result);
    }
}

@FunctionalInterface
interface Function<T, R> {
    R apply(T t);
}