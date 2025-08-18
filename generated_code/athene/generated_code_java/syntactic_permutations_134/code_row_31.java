import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class DecoratorExample {
    private Map<String, Function<String, String>> urlMap = new HashMap<>();

    public static void main(String[] args) {
        DecoratorExample decoratorExample = new DecoratorExample();
        decoratorExample.route("/hello", DecoratorExample::hello);
        System.out.println(decoratorExample.urlMap.get("/hello").apply("JohnDoe"));
    }

    public void route(String url, Function<String, String> handler) {
        urlMap.put(url, username -> escape(handler.apply(username)));
    }

    public static String hello(String username) {
        return "Hello " + username;
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }
}