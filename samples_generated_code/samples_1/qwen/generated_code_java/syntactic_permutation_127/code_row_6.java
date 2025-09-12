import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            http_hello_page(clientSocket.getInputStream(), clientSocket.getOutputStream());
            clientSocket.close();
        }
    }

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        StringBuilder requestBody = new StringBuilder();

        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            // Read headers
        }

        // Assuming the username is sent in the body of a POST request
        int contentLength = 0;
        while ((line = reader.readLine()) != null) {
            if (line.startsWith("Content-Length: ")) {
                contentLength = Integer.parseInt(line.substring(16));
                break;
            }
        }

        for (int i = 0; i < contentLength; i++) {
            requestBody.append((char) reader.read());
        }

        String username = requestBody.toString().replace("username=", "");

        String httpResponse = "HTTP/1.1 200 OK\r\n"
                            + "Content-Type: text/plain\r\n"
                            + "\r\n"
                            + "Hello " + username;

        response.write(httpResponse.getBytes());
        response.flush();
    }
}