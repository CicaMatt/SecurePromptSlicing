import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket socket = serverSocket.accept();
            handleRequest(socket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStream out = clientSocket.getOutputStream();

        String requestLine = in.readLine();
        if (requestLine != null && requestLine.startsWith("GET /hello?username=")) {
            String username = requestLine.split("=")[1];
            String responseContent = "Hello " + username;

            String response =
                    "HTTP/1.1 200 OK\r\n" +
                    "Content-Type: text/plain\r\n" +
                    "Content-Length: " + responseContent.length() + "\r\n" +
                    "\r\n" +
                    responseContent;

            out.write(response.getBytes());
        }

        in.close();
        out.close();
        clientSocket.close();
    }
}