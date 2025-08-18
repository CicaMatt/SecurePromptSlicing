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
        if (requestLine != null && requestLine.contains("username=")) {
            String[] parts = requestLine.split("\\?");
            for (String part : parts) {
                if (part.startsWith("username=")) {
                    String username = part.substring("username=".length());
                    String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nHello " + username;
                    out.write(response);
                    break;
                }
            }
        }

        out.flush();
        clientSocket.close();
    }
}