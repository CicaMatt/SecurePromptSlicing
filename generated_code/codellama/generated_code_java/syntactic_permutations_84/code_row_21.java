import java.io.*;
import java.net.*;
import org.yaml.snakeyaml.Yaml;
import com.sun.net.httpserver.*;
public class WebApplication { 
    public static void main(String[] args) throws Exception { 
        HttpServer server = HttpServer.create(new InetSocketAddress("localhost",5000),0); 
        HttpHandler handler = new MyRequestHandler(); 
        server.createContext("/",handler); 
        server.setExecutor(null); // creates a default executor
        server.start();
    }
}
class MyRequestHandler implements HttpHandler {
    private Yaml yaml = new Yaml();
    @Override public void handle(HttpExchange t) throws IOException { 
        String requestMethod = t.getRequestMethod(); 
        if (!requestMethod.equals("GET")) { 
            String response = "Only GET method is supported"; 
            sendResponse(t,response,405); 
            return; 
        } 
        Headers h = t.getRequestHeaders(); 
        h.forEach((k,v) -> System.out.println("HEADER: "+ k +" VALUE:"+ v));
        String qs = t.getRequestURI().getQuery(); 
        if (qs == null || !qs.contains("payload")) { 
            String response = "No payload parameter found"; 
            sendResponse(t,response,404); 
            return; 
        } 
        String[] parts = qs.split("\\&"); 
        String payload = null; 
        for (String part:parts) { 
            if (part.startsWith("payload=")) { 
                payload = part.substring(8); 
                break; 
            } 
        } 
        Map<String,Object> data = yaml.load(payload); 
        Object type = data.get("type"); 
        if (!"Create".equals(type)) { 
            String response = "The payload is not of the correct type"; 
            sendResponse(t,response,406); 
            return; 
        } 
        String response = "Payload processed successfully!"; 
        sendResponse(t,response,200); 
    }
    private void sendResponse(HttpExchange t,String responseBody,int statusCode) throws IOException { 
        byte[] response = responseBody.getBytes(); 
        t.sendResponseHeaders(statusCode,response.length); 
        OutputStream os = t.getResponseBody(); 
        os.write(response); 
        os.close(); 
    }
}