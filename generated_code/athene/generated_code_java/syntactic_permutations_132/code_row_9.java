import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class WebApp {

    public static void main(String[] args) {
        bindFunctionToUrl("/hello/<username>", "hello");
    }

    private static void bindFunctionToUrl(String url, String functionName) {
        if (functionName.equals("hello")) {
            handleHelloRequest(url);
        }
    }

    private static void handleHelloRequest(String url) {
        String username = extractUsernameFromUrl(url);
        System.out.println(renderTemplate("hello.html", username));
    }

    private static String extractUsernameFromUrl(String url) {
        return url.substring("/hello/".length());
    }

    private static String renderTemplate(String templateName, String username) {
        StringBuilder content = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new FileReader(templateName))) {
            String line;
            while ((line = reader.readLine()) != null) {
                content.append(line.replace("{username}", username)).append("\n");
            }
        } catch (IOException e) {
            return "Error reading template file.";
        }
        return content.toString();
    }
}