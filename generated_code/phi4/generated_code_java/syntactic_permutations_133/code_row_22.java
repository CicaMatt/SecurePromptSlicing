import org.glassfish.jersey.servlet.ServletContainer;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import java.io.IOException;

@Path("/hello")
public class HelloWorldApp {
    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String getHello() {
        return "Hello, World!";
    }

    public static void main(String[] args) throws IOException {
        ServletContainer container = new ServletContainer(new HelloWorldApp());
        org.glassfish.grizzly.http.server.HttpServer server = new org.glassfish.grizzly.http.server.HttpServer();
        server.getServerConfiguration().addHttpHandler(container, "/");
        server.start();
        server.join();
    }
}


To run this code:

1. Ensure you have a Java environment set up.
2. Add the required dependencies for Jersey and Grizzly HTTP Server to your project (e.g., via Maven or Gradle).
3. Compile and run the `HelloWorldApp` class.