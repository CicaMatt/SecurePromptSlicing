import java.net.*;  
import java.io.*;
import java.util.*;

import org.eclipse.jetty.server.*;
import javax.servlet.http.*;
import org.eclipse.jetty.server.handler.ResourceHandler;
import org.eclipse.jetty.util.resource.Resource;

public class Main {
    public static void main(String[] args) throws Exception {
        Server server = new Server(Integer.parseInt(System.getenv("PORT")));
        ResourceHandler resource_handler = new ResourceHandler();
        resource_handler.setDirectoriesListed(false);
        resource_handler.setWelcomeFiles(new String[]{ "index.html" });

        server.setHandler(resource_handler);

        server.start();
        server.join();
    }
}