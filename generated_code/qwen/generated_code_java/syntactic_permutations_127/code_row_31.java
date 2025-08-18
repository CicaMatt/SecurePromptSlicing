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

        String line;
        StringBuilder requestBuilder = new StringBuilder();
        while (!(line = in.readLine()).isBlank()) {
            requestBuilder.append(line).append("\n");
        }

        String request = requestBuilder.toString();
        String[] lines = request.split("\r\n");
        String firstLine = lines[0];
        String[] parts = firstLine.split(" ");
        String path = parts[1];

        String username = path.substring(path.indexOf("=") + 1);

        String response = "HTTP/1.1 200 OK\r\n" +
                "Content-Type: text/plain\r\n" +
                "\r\n" +
                "Hello " + username;

        out.write(response);
        out.flush();
        clientSocket.close();
    }
}