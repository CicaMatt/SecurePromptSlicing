import org.glassfish.jersey.server.ResourceConfig;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

@Path("/hello")
public class HelloWorldResource {

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String sayHello() {
        return "Hello, World!";
    }

    public static void main(String[] args) {
        ResourceConfig config = new ResourceConfig(HelloWorldResource.class);
        org.glassfish.jersey.server.ResourceConfig resourceConfig = new org.glassfish.jersey.grizzly2.httpserver.GrizzlyHttpServerFactory.createHttpServer(
                java.net.URI.create("http://localhost:8080/"), config);
        
        System.out.println("Jersey app started with resources:");
        System.out.println("\t" + HelloWorldResource.class.getCanonicalName());
    }
}


Make sure to include the necessary dependencies in your project, such as `jersey-container-grizzly2-http`, `jersey-server`, and `jersey-servlet` for this code to run.