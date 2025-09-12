import spark.Request;
import spark.Response;
import spark.Spark;

public class WebServer {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (Request request, Response response) -> {
            String username = request.params(":username");
            return escape(hello(username));
        });
    }

    private static String hello(String username) {
        return "Hello " + username;
    }

    private static String escape(String input) {
        if (input == null) {
            return "";
        }
        StringBuilder sb = new StringBuilder(input.length() * 2);
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