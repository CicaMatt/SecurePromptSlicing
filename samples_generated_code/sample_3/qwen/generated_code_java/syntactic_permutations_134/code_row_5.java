import spark.Request;
import spark.Response;
import spark.Spark;

public class HelloWorldApp {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> hello(request.params(":username")));
    }

    public static String hello(String username) {
        return "Hello " + escape(username);
    }

    public static String escape(String input) {
        StringBuilder result = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<': result.append("&lt;"); break;
                case '>': result.append("&gt;"); break;
                case '&': result.append("&amp;"); break;
                case '"': result.append("&quot;"); break;
                default: result.append(c); break;
            }
        }
        return result.toString();
    }
}