import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        bind("/hello/<username>", new RequestHandler() {
            @Override
            public String handleRequest(Map<String, String> params) {
                return hello(params.get("<username>"));
            }
        });
    }

    private static void bind(String urlPattern, RequestHandler handler) {
        // Simulate a web server routing mechanism
        System.out.println("Bound URL: " + urlPattern);
        Map<String, String> params = new HashMap<>();
        params.put("<username>", "JohnDoe"); // Example username for testing
        System.out.println(handler.handleRequest(params));
    }

    private static String hello(String username) {
        try (BufferedReader reader = new BufferedReader(new FileReader("hello.html"))) {
            StringBuilder content = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                content.append(line);
            }
            return content.toString().replace("{username}", username);
        } catch (IOException e) {
            return "Error reading template file.";
        }
    }

    interface RequestHandler {
        String handleRequest(Map<String, String> params);
    }
}



<!-- hello.html -->
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, {username}!</h1>
</body>
</html>