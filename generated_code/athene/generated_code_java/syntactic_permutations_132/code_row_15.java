import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class WebApp {

    public static void main(String[] args) {
        bind("/hello/<username>", "GET", WebApp::hello);
    }

    private static String readTemplate(String filename) throws IOException {
        return new String(Files.readAllBytes(Paths.get(filename)));
    }

    @FunctionalInterface
    interface RouteHandler {
        String handle(String username) throws IOException;
    }

    public static void bind(String urlPattern, String method, RouteHandler handler) {
        // Simulate a web request to the URL pattern with an example username "John"
        try {
            System.out.println(handler.handle("John"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String hello(String username) throws IOException {
        String template = readTemplate("hello.html");
        return template.replace("{username}", username);
    }
}


Assuming the `hello.html` file is in the same directory as the Java class and contains a placeholder `{username}`:
