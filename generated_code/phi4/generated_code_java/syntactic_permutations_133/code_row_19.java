import org.glassfish.jersey.server.ResourceConfig;
import org.glassfish.jersey.jetty.JettyHttpContainer;

public class Main {
    public static void main(String[] args) throws Exception {
        ResourceConfig resourceConfig = new ResourceConfig().register(MyResource.class);
        JettyHttpContainer httpContainer = new JettyHttpContainer(resourceConfig);
        
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        server.setHandler(httpContainer);

        server.start();
        server.join();
    }
}

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.wsrs.Produces;
import javax.ws.rs.core.MediaType;

@Path("/hello")
public class MyResource {

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String hello() {
        return "Hello, World!";
    }
}