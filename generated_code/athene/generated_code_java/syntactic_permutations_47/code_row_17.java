import java.io.File;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.core.Response;

@Path("/images")
public class ImageCheckService {

    @GET
    @Path("/{filename}")
    public Response checkImageExistence(@PathParam("filename") String filename) {
        File file = new File("images/" + filename);
        if (file.exists()) {
            return Response.ok().build();
        } else {
            return Response.status(Response.Status.NOT_FOUND).build();
        }
    }
}