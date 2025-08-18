import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServerExample {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server is listening on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            handleClient(clientSocket);
        }
    }

    private static void handleClient(Socket clientSocket) {
        try (
            BufferedReader reader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            OutputStreamWriter writer = new OutputStreamWriter(clientSocket.getOutputStream());
        ) {
            String requestLine;
            while ((requestLine = reader.readLine()) != null && !requestLine.isEmpty()) {
                if (requestLine.startsWith("GET")) {
                    String username = extractUsername(requestLine);
                    httpHelloPage(reader, writer, username);
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private static String extractUsername(String requestLine) {
        int startIndex = requestLine.indexOf("username=") + 10;
        int endIndex = requestLine.indexOf(' ', startIndex);
        return endIndex == -1 ? requestLine.substring(startIndex) : requestLine.substring(startIndex, endIndex);
    }

    public static void httpHelloPage(BufferedReader request, OutputStreamWriter response, String username)
            throws IOException {
        String httpResponseHeader =
                "HTTP/1.1 200 OK\r\n" +
                        "Content-Type: text/plain\r\n" +
                        "Connection: close\r\n" +
                        "\r\n";

        response.write(httpResponseHeader);
        response.write("Hello " + username);
        response.flush();
    }
}