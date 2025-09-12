import spark.Request;
import spark.Response;
import spark.Spark;

public class HelloWorld {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (Request request, Response response) -> {
            String username = request.params(":username");
            return escape(hello(username));
        });
    }

    public static String hello(String username) {
        return "Hello " + username;
    }

    public static String escape(String input) {
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