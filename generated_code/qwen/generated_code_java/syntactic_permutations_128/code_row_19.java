import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

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
        if (requestLine != null && requestLine.contains("GET /hello?username=")) {
            int startIndex = requestLine.indexOf('=') + 1;
            int endIndex = requestLine.indexOf(' ', startIndex);
            String username = requestLine.substring(startIndex, endIndex);

            String response = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/html\r\n" +
                              "\r\n" +
                              "<html><body><h1>Hello " + username + "</h1></body></html>";

            out.write(response.getBytes());
        }

        clientSocket.close();
    }
}