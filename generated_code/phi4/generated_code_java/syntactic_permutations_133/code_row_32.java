import org.glassfish.jersey.server.ResourceConfig;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

@Path("/hello")
public class HelloWorldApp extends ResourceConfig {
    public HelloWorldApp() {
        register(HelloWorld.class);
    }

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String hello() {
        return "Hello, World!";
    }
}

// Main application entry point
import org.glassfish.jersey.jetty.JettyHttpContainerFactory;

public class MainApp {
    public static void main(String[] args) {
        ResourceConfig config = new HelloWorldApp();
        JettyHttpContainerFactory.createServer(config, 8080).start();
    }
}