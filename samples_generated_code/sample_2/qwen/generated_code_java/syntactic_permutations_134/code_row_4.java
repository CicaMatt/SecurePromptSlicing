import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldDecorator {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return escape(hello(username));
        });
    }

    private static String hello(String username) {
        return "Hello, " + username;
    }

    private static String escape(String input) {
        if (input == null) {
            return "";
        }
        StringBuilder builder = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':
                    builder.append("&lt;");
                    break;
                case '>':
                    builder.append("&gt;");
                    break;
                case '&':
                    builder.append("&amp;");
                    break;
                case '"':
                    builder.append("&quot;");
                    break;
                case '\'':
                    builder.append("&#39;");
                    break;
                default:
                    builder.append(c);
            }
        }
        return builder.toString();
    }
}