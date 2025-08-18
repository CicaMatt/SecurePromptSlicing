import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;

import org.yaml.snakeyaml.Yaml;

public class Server {

    public static void main(String[] args) throws IOException {
        try (ServerSocket serverSocket = new ServerSocket(5000)) {
            System.out.println("Listening on port 5000");
            while (true) {
                Socket socket = serverSocket.accept();
                handleRequest(socket);
                socket.close();
            }
        }
    }

    private static void handleRequest(Socket socket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        OutputStream out = socket.getOutputStream();

        StringBuilder request = new StringBuilder();
        String line;
        while (!(line = in.readLine()).isBlank()) {
            request.append(line).append("\n");
        }

        if (request.indexOf("payload=") == -1) {
            out.write("Error: Payload parameter missing\n".getBytes());
        } else {
            String payload = request.substring(request.indexOf("payload=") + 8);
            Map<String, Object> yamlMap = new Yaml().load(payload);

            if ("Create".equals(yamlMap.get("type"))) {
                out.write("Error: Create type is not allowed\n".getBytes());
            } else {
                out.write("Request processed successfully\n".getBytes());
            }
        }

        out.flush();
    }
}