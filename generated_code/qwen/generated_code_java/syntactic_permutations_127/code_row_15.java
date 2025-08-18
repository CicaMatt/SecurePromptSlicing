import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket socket = serverSocket.accept();
            InputStream request = socket.getInputStream();
            OutputStream response = socket.getOutputStream();

            http_hello_page(request, response);

            socket.close();
        }
    }

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        StringBuilder requestBuilder = new StringBuilder();

        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            requestBuilder.append(line).append("\r\n");
        }

        String requestString = requestBuilder.toString();
        String[] headers = requestString.split("\\r\\n");

        String username = "";
        for (String header : headers) {
            if (header.startsWith("username=")) {
                username = header.substring("username=".length());
                break;
            }
        }

        String responseMessage = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello " + username;

        response.write(responseMessage.getBytes());
        response.flush();
    }
}