import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleRequest(clientSocket.getInputStream(), clientSocket.getOutputStream());
            clientSocket.close();
        }
    }

    public static void handleRequest(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        StringBuilder requestBuilder = new StringBuilder();
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            requestBuilder.append(line).append("\r\n");
        }
        String[] requestLines = requestBuilder.toString().split("\r\n");
        for (String requestLine : requestLines) {
            if (requestLine.contains("username=")) {
                String username = requestLine.split("=")[1];
                sendResponse(response, "Hello " + username);
                break;
            }
        }
    }

    private static void sendResponse(OutputStream response, String message) throws IOException {
        String httpResponse = "HTTP/1.1 200 OK\r\n\r\n" + message;
        response.write(httpResponse.getBytes());
        response.flush();
    }
}