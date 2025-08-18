import spark.Request;
import spark.Response;
import spark.Spark;

public class HelloWorldDecorator {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (Request request, Response response) -> escape(hello(request.params(":username"))));
    }

    private static String hello(String username) {
        return "Hello " + username;
    }

    private static String escape(String input) {
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
}