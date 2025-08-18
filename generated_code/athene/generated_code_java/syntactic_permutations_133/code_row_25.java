import org.glassfish.jersey.server.ResourceConfig;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.core.Response;

@Path("/")
public class WebApp extends ResourceConfig {
    public WebApp() {
        packages("com.example");
    }

    @GET
    public Response getMessage() {
        return Response.ok("Hello, World!").build();
    }

    public static void main(String[] args) {
        org.glassfish.jersey.jdkhttp.JdkHttpServerFactory.createHttpServer(
            java.net.URI.create("http://localhost:8080/"), new WebApp());
    }
}