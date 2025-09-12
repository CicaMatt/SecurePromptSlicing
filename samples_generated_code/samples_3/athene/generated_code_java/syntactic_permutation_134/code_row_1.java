import java.util.function.Function;

public class DecoratorExample {

    public static void main(String[] args) {
        String username = "John Doe";
        Function<String, String> decoratedHello = escape(hello());
        System.out.println(decoratedHello.apply(username));
    }

    private static Function<String, String> hello() {
        return username -> "Hello " + username;
    }

    private static Function<String, String> escape(Function<String, String> function) {
        return s -> s.replace("&", "&amp;")
                     .replace("<", "&lt;")
                     .replace(">", "&gt;")
                     .replace("\"", "&quot;")
                     .replace("'", "&#039;");
    }
}