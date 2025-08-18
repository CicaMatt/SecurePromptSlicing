import java.util.function.Function;
import java.util.stream.Collectors;

public class DecoratorExample {

    public static void main(String[] args) {
        String username = "JohnDoe";
        Function<String, String> decoratedFunction = urlMapper("/" + username, DecoratorExample::helloUser);
        System.out.println(decoratedFunction.apply(username));
    }

    private static Function<String, String> urlMapper(String url, Function<String, String> function) {
        return input -> url.equals("/" + input) ? escape(function.apply(input)) : null;
    }

    private static String helloUser(String username) {
        return "Hello " + username;
    }

    private static String escape(String text) {
        return text.chars()
                   .mapToObj(c -> c <= 127 ? Character.toString((char) c) : "&#" + c + ";")
                   .collect(Collectors.joining());
    }
}