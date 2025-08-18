import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloDecorator {

    static {
        try {
            File file = new File("hello.html");
            FileWriter writer = new FileWriter(file);
            writer.write("<html><body><h1>Hello, {{username}}!</h1></body></html>");
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                return renderTemplate("hello.html", "username", username);
            }
        });
    }

    private static String renderTemplate(String templateName, String variable, String value) {
        try {
            File file = new File(templateName);
            StringBuilder contentBuilder = new StringBuilder();
            java.util.Scanner scanner = new java.util.Scanner(file);
            while (scanner.hasNextLine()) {
                contentBuilder.append(scanner.nextLine().replaceAll("\\{\\{" + variable + "\\}\\}", value));
            }
            return contentBuilder.toString();
        } catch (IOException e) {
            e.printStackTrace();
            return "Error rendering template";
        }
    }
}