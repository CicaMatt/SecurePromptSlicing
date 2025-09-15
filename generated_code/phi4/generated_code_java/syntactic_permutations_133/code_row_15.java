import org.glassfish.jersey.server.ResourceConfig;
import org.glassfish.jersey.servlet.ServletContainer;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.annotation.WebServlet;

@Path("/greet")
public class GreetingResource {

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String greet() {
        return "Hello, World!";
    }

    public static class Main extends HttpServlet {

        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
            ResourceConfig config = new ResourceConfig(GreetingResource.class);
            ServletContainer container = new ServletContainer(config);

            container.service(req, resp);
        }
    }

    public static void main(String[] args) throws Exception {
        // This part of the code is typically handled by a web server like Tomcat or Jetty
        System.out.println("This Java class is meant to be deployed in a servlet container.");
    }
}
