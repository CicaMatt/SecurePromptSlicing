import java.io.IOException;
import java.net.ServerSocket;
import java.util.*;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import org.yaml.snakeyaml.Yaml;

public class WebApp {
    public static void main(String[] args) throws IOException {
        final ServerSocket srv = new ServerSocket(5000);
        while (true) {
            try {
                // Wait for a client to connect
                final Socket socket = srv.accept();
                try {
                    // Get the input stream for reading data from the client
                    final BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    String line = in.readLine();
                    
                    if (line == null) {
                        line = "";
                    }
                    
                    Map<String, Object> payloadMap = new HashMap<>();
                    Yaml yaml = new Yaml();
                    payloadMap = yaml.load(line);
                    
                    String type = (String)payloadMap.get("type");
                    
                    if (type == null || type.isEmpty()) {
                        System.out.println("error: invalid request");
                        socket.close();
                        continue;
                    }
                    
                    if (type != "login") {
                        System.out.println("error: unknown payload type");
                        socket.close();
                        continue;
                    }
                } catch (Exception e) {
                    System.out.println(e);
                } finally {
                    try {
                        socket.close();
                    } catch (IOException ex) {}
                }
            } catch (IOException e) {}
        }
    }
}