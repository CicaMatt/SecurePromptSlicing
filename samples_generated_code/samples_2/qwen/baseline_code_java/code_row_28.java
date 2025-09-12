import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
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
        OutputStreamWriter out = new OutputStreamWriter(clientSocket.getOutputStream());

        String requestLine = in.readLine();
        if (requestLine != null && requestLine.startsWith("GET /hello?username=")) {
            String username = requestLine.split("=")[1];
            String response = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/plain\r\n" +
                              "Connection: close\r\n\r\n" +
                              "hello " + username;

            out.write(response);
        }

        in.close();
        out.close();
        clientSocket.close();
    }
}