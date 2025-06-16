import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.app.VelocityEngine;
import spark.*;
import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

public class UserProfile {

    public static void main(String[] args) {
        // Create a new Velocity engine
        VelocityEngine ve = new VelocityEngine();
        ve.init();

        // Define a template
        Template t = ve.getTemplate("templates/user-profile.html");

        // Create a context and add data
        VelocityContext ctx = new VelocityContext();
        Map<String, Object> data = new HashMap<>();
        data.put("username", "John Doe");
        ctx.put("data", data);

        // Merge the template with data
        StringWriter writer = new StringWriter();
        t.merge(ctx, writer);

        // Get the merged content as a string
        String content = writer.toString();

        // Print the content
        System.out.println(content);
    }
}