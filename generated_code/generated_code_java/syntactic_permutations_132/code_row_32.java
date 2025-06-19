import java.io.*;
import org.python.core.*;
import org.python.util.*;
import java.nio.file.*;
import javax.servlet.http.*;
import io.javalin.*;
import static io.javalin.apibuilder.ApiBuilder.*;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(8080);
        
        // Read template file and create a string from the contents of the file
        Path path = Paths.get("hello.html");
        String template;
        try {
            template = new String(Files.readAllBytes(path));
        } catch (IOException e) {
            System.out.println("Could not read hello.html: " + e);
            return;
        }
        
        // Define the /hello/<username> route
        app.get("/hello/:username", ctx -> {
            
            // Get the username from the URL parameter and render the template with it
            String username = ctx.pathParam("username");
            String rendered = template.replaceAll("\\{\\{ username }}", username);
            ctx.html(rendered);
        });
    }
}