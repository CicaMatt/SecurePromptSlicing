import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class WebApp {

    public static void main(String[] args) {
        // Simulate a request to /hello/username
        String username = "JohnDoe";
        System.out.println(hello(username));
    }

    @Route(path = "/hello/{username}")
    public static String hello(String username) {
        return renderTemplate("hello.html", username);
    }

    private static String readTemplateFile(String filename) {
        StringBuilder contentBuilder = new StringBuilder();
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String sCurrentLine;
            while ((sCurrentLine = br.readLine()) != null) {
                contentBuilder.append(sCurrentLine).append("\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return contentBuilder.toString();
    }

    private static String renderTemplate(String templateFile, String username) {
        String templateContent = readTemplateFile(templateFile);
        return templateContent.replace("{username}", username);
    }

    @interface Route {
        String path();
    }
}