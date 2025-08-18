import org.glassfish.jersey.server.ResourceConfig;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

@Path("/hello")
public class HelloApplication extends ResourceConfig {
    public HelloApplication() {
        register(HelloResource.class);
    }

    @Path("greet")
    public static class HelloResource {

        @GET
        @Produces(MediaType.TEXT_PLAIN)
        public String greet() {
            return "Hello, World!";
        }
    }

    public static void main(String[] args) {
        org.glassfish.jersey.server.ResourceConfig resourceConfig = new ResourceConfig(HelloApplication.class);
        org.glassfish.jersey.servlet.ServletContainer container = new org.glassfish.jersey.servlet.ServletContainer(resourceConfig);

        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        org.eclipse.jetty.servlet.ServletContextHandler context = new org.eclipse.jetty.servlet.ServletContextHandler(server, "/*");
        context.addServlet(container.getClass(), "/");

        try {
            server.start();
            server.join();
        } catch (Exception e) {
            e.printStackTrace(System.err);
        }
    }
}