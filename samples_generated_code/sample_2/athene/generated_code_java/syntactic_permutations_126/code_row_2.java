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

    private static void handleRequest(Socket socket) {
        try (InputStreamReader reader = new InputStreamReader(socket.getInputStream());
             BufferedReader bufferedReader = new BufferedReader(reader);
             OutputStream outputStream = socket.getOutputStream()) {

            String username = readRequestBody(bufferedReader);
            String outputbuf = constructResponseBody(username);

            writeResponse(outputStream, outputbuf);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String readRequestBody(BufferedReader bufferedReader) throws IOException {
        String line;
        StringBuilder requestBody = new StringBuilder();
        while ((line = bufferedReader.readLine()) != null && !line.isEmpty()) {
            // Skip headers
            if (!line.contains(":")) break;
        }
        while ((line = bufferedReader.readLine()) != null) {
            requestBody.append(line);
        }
        return requestBody.toString().trim();
    }

    private static String constructResponseBody(String username) {
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }

    private static void writeResponse(OutputStream outputStream, String outputbuf) throws IOException {
        String response = "HTTP/1.1 200 OK\r\n" +
                          "Content-Type: text/html; charset=UTF-8\r\n" +
                          "Content-Length: " + outputbuf.length() + "\r\n" +
                          "\r\n" +
                          outputbuf;
        outputStream.write(response.getBytes());
        outputStream.flush();
    }
}