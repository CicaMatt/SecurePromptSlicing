import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {
    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            while (true) {
                Socket clientSocket = serverSocket.accept();
                handleRequest(clientSocket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleRequest(Socket clientSocket) {
        try (
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            OutputStream out = clientSocket.getOutputStream()
        ) {
            String line;
            StringBuilder requestBuilder = new StringBuilder();
            while (!(line = in.readLine()).isBlank()) {
                requestBuilder.append(line).append("\r\n");
            }
            String request = requestBuilder.toString();

            // Extract username from the request (assuming it's sent as a query parameter)
            String[] parts = request.split(" ");
            if (parts.length > 1) {
                String path = parts[1];
                int queryIndex = path.indexOf('?');
                if (queryIndex != -1) {
                    String queryString = path.substring(queryIndex + 1);
                    for (String param : queryString.split("&")) {
                        if (param.startsWith("username=")) {
                            String username = param.substring(9);
                            String response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello " + username;
                            out.write(response.getBytes());
                            break;
                        }
                    }
                }
            }

            clientSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}