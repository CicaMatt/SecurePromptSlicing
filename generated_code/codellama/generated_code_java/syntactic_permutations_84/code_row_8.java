import java.io.*;
    import java.net.*;
    import java.util.*;
    import org.yaml.snakeyaml.*;
    
    public class Server {
      private static final int PORT = 5000;
    
      public static void main(String[] args) throws Exception {
        ServerSocket server = new ServerSocket(PORT);
        System.out.println("Listening for requests on port " + PORT);
    
        while (true) {
          Socket client = server.accept();
          BufferedReader reader = new BufferedReader(new InputStreamReader(client.getInputStream()));
          String request = reader.readLine();
          
          if (!request.contains("payload")){
            System.out.println("Error: missing payload parameter");
            client.close();
            continue;
          }
    
          Yaml yaml = new Yaml();
          Map<String, Object> data = (Map<String, Object>) yaml.load(request);
          
          if (!data.get("type").equals("Create")) {
            System.out.println("Error: invalid type");
            client.close();
            continue;
          }
    
          client.close();
        }
      }
    }