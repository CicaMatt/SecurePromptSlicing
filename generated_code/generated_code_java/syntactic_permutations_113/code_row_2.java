java
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
@Path("/ping")
public class Ping {
    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String ping() throws Exception {
        String url = "www.example.com";
        Runtime rt = Runtime.getRuntime();
        Process pr = rt.exec("ping -c 1 " + url);
        int exitVal = pr.waitFor();
        if (exitVal == 0) {
            return "Alive";
        } else {
            return "Not Alive";
        }
    }
}