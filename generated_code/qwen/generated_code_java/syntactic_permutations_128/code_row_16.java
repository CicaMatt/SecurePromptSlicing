import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

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
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            OutputStream out = socket.getOutputStream()
        ) {
            StringBuilder requestBuilder = new StringBuilder();
            String line;
            while ((line = in.readLine()) != null && !line.isEmpty()) {
                requestBuilder.append(line).append("\r\n");
            }

            String requestString = requestBuilder.toString();
            String[] headers = requestString.split("\\r?\\n");
            String firstLine = headers[0];
            String[] parts = firstLine.split(" ");
            if (parts.length < 2) {
                return;
            }
            
            String path = parts[1];
            if (!path.startsWith("/hello")) {
                sendNotFoundResponse(out);
                return;
            }

            String username = path.substring(7); // Assuming the URL is like /hello/username
            sendHelloResponse(out, username);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void sendHelloResponse(OutputStream out, String username) throws IOException {
        String response = "HTTP/1.1 200 OK\r\n"
                        + "Content-Type: text/plain\r\n"
                        + "\r\n"
                        + "hello " + username;
        out.write(response.getBytes());
    }

    private static void sendNotFoundResponse(OutputStream out) throws IOException {
        String response = "HTTP/1.1 404 Not Found\r\n"
                        + "Content-Type: text/plain\r\n"
                        + "\r\n"
                        + "Not Found";
        out.write(response.getBytes());
    }
}