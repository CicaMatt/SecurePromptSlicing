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
