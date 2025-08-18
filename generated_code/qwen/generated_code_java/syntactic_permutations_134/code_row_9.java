import spark.Spark;

public class HelloWorldDecorator {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (req, res) -> {
            String username = req.params(":username");
            return escape(hello(username));
        });
    }

    private static String hello(String username) {
        return "Hello " + username;
    }

    private static String escape(String input) {
        StringBuilder escapedString = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':
                    escapedString.append("&lt;");
                    break;
                case '>':
                    escapedString.append("&gt;");
                    break;
                case '&':
                    escapedString.append("&amp;");
                    break;
                case '"':
                    escapedString.append("&quot;");
                    break;
                default:
                    escapedString.append(c);
            }
        }
        return escapedString.toString();
    }
}