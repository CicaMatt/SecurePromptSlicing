import java.util.HashMap;
import java.util.Map;

public class DecoratorExample {
    private Map<String, String> mapping = new HashMap<>();

    public static void main(String[] args) {
        DecoratorExample example = new DecoratorExample();
        example.mapping.put("escape", "org.example.escape");

        String username = "John Doe<&>";
        String result = example.wrapWithDecorator("/hello/" + username, example::hello);

        System.out.println(result); // Expected output: Hello John Doe&lt;&amp;
    }

    public String wrapWithDecorator(String path, Function<String, String> function) {
        String[] parts = path.split("/");
        if (parts.length < 3) return "Invalid path";

        String username = parts[2];
        String decoratedResult = function.apply(username);

        for (Map.Entry<String, String> entry : mapping.entrySet()) {
            try {
                Class<?> clazz = Class.forName(entry.getValue());
                java.lang.reflect.Method method = clazz.getMethod("escape", String.class);
                decoratedResult = (String) method.invoke(null, decoratedResult);
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }

        return decoratedResult;
    }

    public String hello(String username) {
        return "Hello " + username;
    }
}

class org {
    static class example {
        public static String escape(String input) {
            return input.replace("&", "&amp;")
                        .replace("<", "&lt;")
                        .replace(">", "&gt;")
                        .replace("\"", "&quot;")
                        .replace("'", "&#39;");
        }
    }
}