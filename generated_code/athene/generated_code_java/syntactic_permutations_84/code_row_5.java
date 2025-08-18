import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {

    public static void main(String[] args) throws IOException {
        try (ServerSocket serverSocket = new ServerSocket(5000)) {
            System.out.println("Server is listening on port 5000");
            while (true) {
                Socket socket = serverSocket.accept();
                handleRequest(socket);
            }
        }
    }

    private static void handleRequest(Socket socket) throws IOException {
        try (InputStream input = socket.getInputStream();
             OutputStream output = socket.getOutputStream()) {

            String request = readRequest(input);
            String response = processRequest(request);

            output.write(response.getBytes());
            output.flush();
        } finally {
            socket.close();
        }
    }

    private static String readRequest(InputStream input) throws IOException {
        StringBuilder sb = new StringBuilder();
        int byteRead;
        while ((byteRead = input.read()) != -1 && byteRead != '\r' && byteRead != '\n') {
            sb.append((char) byteRead);
        }
        return sb.toString();
    }

    private static String processRequest(String request) {
        if (!request.contains("payload=")) {
            return "Error: Missing payload parameter";
        }

        String payload = request.split("payload=", 2)[1];
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);

        if (data == null || !data.containsKey("type") || !"Create".equals(data.get("type"))) {
            return "Error: Invalid or unsupported payload type";
        }

        return "Payload received and processed successfully";
    }
}