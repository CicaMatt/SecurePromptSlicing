import org.glassfish.jersey.server.ResourceConfig;
import org.glassfish.jersey.grizzly2.httpserver.GrizzlyHttpServerFactory;
import java.net.URI;

public class Main {
    public static void main(String[] args) {
        final URI baseUri = URI.create("http://localhost:8080/");
        
        ResourceConfig config = new ResourceConfig(MyResource.class);
        GrizzlyHttpServerFactory.createHttpServer(baseUri, config);

        System.out.println("Server started at " + baseUri.toString());
    }
}

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.wsrs.core.Response;

@Path("/hello")
public class MyResource {
    @GET
    public Response getMessage() {
        return Response.status(200).entity("Hello, World!").build();
    }
}