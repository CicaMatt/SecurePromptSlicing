import java.io.*;
import java.net.*;
import java.util.*;
import java.lang.StringBuilder;
import org.yaml.snakeyaml.Yaml;

public class WebServer {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/", new RequestHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }
}