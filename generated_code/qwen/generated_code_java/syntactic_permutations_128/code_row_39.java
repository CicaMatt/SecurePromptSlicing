import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = server.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStreamWriter out = new OutputStreamWriter(clientSocket.getOutputStream());

        String line;
        StringBuilder requestBuilder = new StringBuilder();
        while (!(line = in.readLine()).isBlank()) {
            requestBuilder.append(line).append("\r\n");
        }

        String request = requestBuilder.toString();
        String[] requestLines = request.split("\r\n");
        String firstLine = requestLines[0];
        String[] parts = firstLine.split(" ");
        if (parts.length >= 2) {
            String path = parts[1];
            String username = path.substring(1); // Remove the leading '/'
            String responseMessage = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello " + username;
            out.write(responseMessage);
        }

        out.flush();
        clientSocket.close();
    }
}