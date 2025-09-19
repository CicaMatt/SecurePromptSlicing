import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldDecorator {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> escape(hello(request.params(":username"))));
    }

    public static String hello(String username) {
        return "Hello " + username;
    }

    public static String escape(String input) {
        StringBuilder escaped = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<': escaped.append("&lt;"); break;
                case '>': escaped.append("&gt;"); break;
                case '&': escaped.append("&amp;"); break;
                case '"': escaped.append("&quot;"); break;
                case '\'': escaped.append("&#x27;"); break;
                default: escaped.append(c);
            }
        }
        return escaped.toString();
    }
}