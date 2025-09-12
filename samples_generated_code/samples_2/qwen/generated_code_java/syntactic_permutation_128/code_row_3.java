import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            System.out.println("Server is listening on port 8080");
            while (true) {
                Socket socket = serverSocket.accept();
                handleRequest(socket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleRequest(Socket socket) throws IOException {
        try (
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            OutputStream out = socket.getOutputStream()
        ) {
            StringBuilder requestBuilder = new StringBuilder();
            String line;
            while (!(line = in.readLine()).isBlank()) {
                requestBuilder.append(line).append("\r\n");
            }
            String request = requestBuilder.toString();

            String[] lines = request.split("\\r\\n");
            if (lines.length > 0) {
                String[] parts = lines[0].split(" ");
                if (parts.length == 3 && "GET".equalsIgnoreCase(parts[0])) {
                    String path = parts[1];
                    int usernameStart = path.indexOf("username=");
                    if (usernameStart != -1) {
                        String username = path.substring(usernameStart + 9);
                        String response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello " + username;
                        out.write(response.getBytes());
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            socket.close();
        }
    }
}