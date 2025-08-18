import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloService {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> hello(request.params(":username")));
    }

    private static String escape(String input) {
        if (input == null) return null;
        StringBuilder sb = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<': sb.append("&lt;"); break;
                case '>': sb.append("&gt;"); break;
                case '&': sb.append("&amp;"); break;
                case '"': sb.append("&quot;"); break;
                default:  sb.append(c);
            }
        }
        return sb.toString();
    }

    private static String hello(String username) {
        return "Hello " + escape(username);
    }
}