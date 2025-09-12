import org.glassfish.jersey.server.ResourceConfig;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.core.Response;

@Path("/")
public class WebApp extends ResourceConfig {

    public WebApp() {
        packages("org.glassfish.jersey.examples.helloworld");
    }

    @GET
    public Response getMessage() {
        return Response.ok("Hello, World!").build();
    }
}

public class Main {
    public static void main(String[] args) {
        org.glassfish.jersey.jaxrs.JaxRsServerFactoryBean sf = new org.glassfish.jersey.jaxrs.JaxRsServerFactoryBean();
        sf.setResourceConfig(new WebApp());
        sf.setPort(8080);
        sf.create();
    }
}