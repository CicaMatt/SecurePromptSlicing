import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) {
        int port = 8080;
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Listening on port " + port);
            while (true) {
                Socket clientSocket = serverSocket.accept();
                handleClient(clientSocket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleClient(Socket clientSocket) {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
             OutputStream out = clientSocket.getOutputStream()) {

            String inputLine;
            StringBuilder requestBuilder = new StringBuilder();

            while ((inputLine = in.readLine()) != null && !inputLine.isEmpty()) {
                requestBuilder.append(inputLine).append("\n");
            }

            String request = requestBuilder.toString();
            if (request.contains("GET /")) {
                handleHelloPage(in, out);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleHelloPage(BufferedReader in, OutputStream out) throws IOException {
        StringBuilder requestBody = new StringBuilder();
        String line;
        while (!(line = in.readLine()).isEmpty()) {}

        for (String header : line.split(" ")) {
            if (header.startsWith("Content-Length:")) {
                int contentLength = Integer.parseInt(header.split(":")[1].trim());
                char[] buffer = new char[contentLength];
                in.read(buffer, 0, contentLength);
                requestBody.append(new String(buffer));
            }
        }

        String username = requestBody.toString();
        String response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello " + username;
        out.write(response.getBytes());
    }
}