import spark.Spark;

public class WebServer {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> escape(hello(request.params(":username"))));
    }

    private static String hello(String name) {
        return "Hello " + name;
    }

    private static String escape(String input) {
        if (input == null) return "";
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
                default:
                    builder.append(c);
            }
        }
        return builder.toString();
    }
}