java 
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import org.glassfish.jersey.servlet.ServletContainer;

public class MyApplication extends javax.ws.rs.core.Application {
    public static void main(String[] args) throws Exception{
        Server server = new Server(8080);
        ServletHandler handler = new ServletHandler();
        ServletHolder servletHolder = new ServletHolder(new ServletContainer(new MyApplication()));
        handler.addServletWithMapping(servletHolder, "/*");
        server.setHandler(handler);
        server.start();
    }
}