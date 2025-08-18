import java.net.URI;
import javax.ws.rs.core.Response;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;

@Path("/redirect")
public class RedirectService {

    @GET
    @Produces("text/plain")
    public Response redirectUrl(@QueryParam("url") String url) {
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();

            if ("example.com".equals(domainName)) {
                return Response.temporaryRedirect(URI.create(url)).build();
            } else {
                return Response.status(Response.Status.NOT_FOUND).entity("404 Not Found").build();
            }
        } catch (Exception e) {
            return Response.status(Response.Status.BAD_REQUEST)
                    .entity("Invalid URL")
                    .build();
        }
    }

    public static void main(String[] args) {
        // The server setup and running logic should be implemented here
        // For a complete example, consider using a framework like Jersey to deploy this service
    }
}