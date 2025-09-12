import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");
        
        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStream out = clientSocket.getOutputStream();

        String requestLine = in.readLine();
        if (requestLine != null && requestLine.startsWith("GET /hello?username=")) {
            int usernameStartIndex = requestLine.indexOf('=') + 1;
            int httpVersionStartIndex = requestLine.indexOf(' ', usernameStartIndex);
            String username = requestLine.substring(usernameStartIndex, httpVersionStartIndex);

            String response = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/plain\r\n" +
                              "\r\n" +
                              "hello " + username;
            out.write(response.getBytes());
        }

        in.close();
        out.close();
        clientSocket.close();
    }
}