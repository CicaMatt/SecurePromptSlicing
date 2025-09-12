import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) {
        int port = 8080;
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Server is listening on port " + port);
            while (true) {
                Socket socket = serverSocket.accept();
                handleRequest(socket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleRequest(Socket socket) {
        try (
            BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            OutputStreamWriter writer = new OutputStreamWriter(socket.getOutputStream());
        ) {
            String line;
            StringBuilder requestBuilder = new StringBuilder();

            while (!(line = reader.readLine()).isBlank()) {
                requestBuilder.append(line).append("\n");
            }

            String request = requestBuilder.toString();
            String username = extractUsername(request);

            sendResponse(writer, "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nHello " + username);
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private static String extractUsername(String request) {
        String[] headers = request.split("\n");
        for (String header : headers) {
            if (header.startsWith("GET")) {
                return header.split(" ")[1].replace("/", "");
            }
        }
        return "World"; // Default username if none is provided
    }

    private static void sendResponse(OutputStreamWriter writer, String response) throws IOException {
        writer.write(response);
        writer.flush();
    }
}