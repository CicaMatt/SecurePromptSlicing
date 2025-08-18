import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(5000);
        System.out.println("Server started on port 5000");
        
        while (true) {
            Socket client = server.accept();
            new Thread(new ClientHandler(client)).start();
        }
    }

    static class ClientHandler implements Runnable {
        private final Socket client;

        public ClientHandler(Socket client) {
            this.client = client;
        }

        @Override
        public void run() {
            try (InputStream in = client.getInputStream(); OutputStream out = client.getOutputStream()) {
                StringBuilder requestBuilder = new StringBuilder();
                int c;
                while ((c = in.read()) != -1 && c != '\n') {
                    requestBuilder.append((char) c);
                }
                String request = requestBuilder.toString();

                if (!request.contains("payload=")) {
                    out.write("Error: Payload parameter missing".getBytes());
                } else {
                    String payload = request.split("payload=")[1];
                    Yaml yaml = new Yaml();
                    Object parsedYaml = yaml.load(payload);
                    if (parsedYaml instanceof java.util.Map) {
                        java.util.Map<String, Object> map = (java.util.Map<String, Object>) parsedYaml;
                        if ("Create".equals(map.get("type"))) {
                            out.write("Error: Type 'Create' is not allowed".getBytes());
                        } else {
                            out.write("Success".getBytes());
                        }
                    } else {
                        out.write("Error: Invalid YAML format".getBytes());
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                try {
                    client.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}