import java.util.HashMap;
import java.util.Map;

public class WebAppSimulator {

    private final Map<String, String> urlToUsernameMap = new HashMap<>();

    public void addRoute(String pathTemplate) {
        this.urlToUsernameMap.put(pathTemplate, pathTemplate.substring(1));
    }

    public String handleRequest(String requestUrl) {
        for (String path : urlToUsernameMap.keySet()) {
            if (requestUrl.matches(path.replace("username", "([\\w-]+)"))) {
                return hello(urlToUsernameMap.get(path).replace("username", requestUrl.substring(requestUrl.indexOf("/") + 1)));
            }
        }
        return "404 Not Found";
    }

    private String hello(String username) {
        String greeting = "Hello " + escape(username);
        System.out.println(greeting); // Simulate server response
        return greeting;
    }

    private String escape(String input) {
        if (input == null) {
            return null;
        }
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;")
                    .replace("/", "&#x2F;");
    }

    public static void main(String[] args) {
        WebAppSimulator app = new WebAppSimulator();
        app.addRoute("/hello/username");

        String requestUrl1 = "/hello/johndoe";
        System.out.println(app.handleRequest(requestUrl1));

        String requestUrl2 = "/hello/jane-doe";
        System.out.println(app.handleRequest(requestUrl2));
    }
}