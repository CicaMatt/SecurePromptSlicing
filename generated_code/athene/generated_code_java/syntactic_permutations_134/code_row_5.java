import java.util.function.Function;

public class DecoratorExample {

    public static void main(String[] args) {
        String username = "John_Doe";
        Function<String, String> decoratedHello = url("/hello/" + username, hello());
        System.out.println(decoratedHello.apply(username));
    }

    private static Function<String, String> url(String url, Function<String, String> function) {
        return (String username) -> {
            if (url.startsWith("/hello/")) {
                return function.apply(escape(username));
            }
            throw new IllegalArgumentException("URL does not match the pattern /hello/username");
        };
    }

    private static Function<String, String> hello() {
        return username -> "Hello " + username;
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }
}