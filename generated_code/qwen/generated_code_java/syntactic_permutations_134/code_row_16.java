import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldDecorator {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> hello(request.params(":username")));
    }

    private static String hello(String username) {
        return escape("Hello " + username);
    }

    private static String escape(String input) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
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
}