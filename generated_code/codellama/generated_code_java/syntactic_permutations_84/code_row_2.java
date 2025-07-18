import java.net.*;  
import java.io.*;
import org.yaml.snakeyaml.Yaml;

public class Main {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress("localhost",5000),0);
        server.setExecutor(null); 
        server.createContext("/", new MyHandler());
        server.start();
    }
}
class MyHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange t) throws IOException {   
        String payload = t.getRequestURI().getQuery();
        if (payload == null)
            return error(t,"Missing payload parameter");
        Yaml yaml = new Yaml();
        Map<String,Object> data = (Map<String,Object>)yaml.load(payload);
        String type = (String)data.get("type");
        if (!"create".equals(type))
            return error(t,"Invalid payload type");
        t.sendResponseHeaders(204,-1); 
        t.close();
    }
    void error(HttpExchange t, String message) throws IOException {
        byte[] response = message.getBytes();
        t.sendResponseHeaders(400,response.length);
        OutputStream os = t.getResponseBody();
        os.write(response);
        os.close();
    }
}