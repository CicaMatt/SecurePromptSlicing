import java.io.*;
import java.net.*;
import java.util.*;
import org.yaml.snakeyaml.Yaml;

public class Server {
    public static void main(String[] args) throws Exception {
        ServerSocket server = new ServerSocket(5000);
        while (true) {
            Socket client = server.accept();
            Yaml yaml = new Yaml();
            Map<String, String> data = yaml.load(new InputStreamReader(client.getInputStream()));
            if (!data.containsKey("payload")) {
                sendErrorMessage(client);
                continue;
            }
            Map<String, Object> payload = yaml.load(data.get("payload"));
            if (!"Create".equals(payload.get("type"))) {
                sendErrorMessage(client);
                continue;
            }
            System.out.println("Success");
        }
    }
    private static void sendErrorMessage(Socket client) throws IOException {
        PrintWriter writer = new PrintWriter(client.getOutputStream());
        writer.print("{\"error\":\"Invalid payload type\"}");
        writer.close();
    }
}