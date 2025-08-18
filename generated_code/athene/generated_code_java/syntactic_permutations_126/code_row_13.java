import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        System.out.println("HTTP Hello Server started on port 8080");

        while (true) {
            Socket clientSocket = server.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket socket) {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
             OutputStream out = socket.getOutputStream()) {

            String username = readRequestBody(in);
            String outputbuf = http_hello_page(username);

            out.write("HTTP/1.1 200 OK\r\n".getBytes());
            out.write("Content-Type: text/html; charset=UTF-8\r\n".getBytes());
            out.write(("Content-Length: " + outputbuf.length() + "\r\n").getBytes());
            out.write("\r\n".getBytes());
            out.write(outputbuf.getBytes());
            out.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String readRequestBody(BufferedReader in) throws IOException {
        StringBuilder body = new StringBuilder();
        String line;
        boolean isBodyStarted = false;
        while ((line = in.readLine()) != null && !line.isEmpty()) {
            if ("POST".equals(line.split(" ")[0])) {
                // Skip headers
                continue;
            }
            if (isBodyStarted) {
                body.append(line);
            } else if (line.isEmpty()) {
                isBodyStarted = true;
            }
        }
        return body.toString();
    }

    private static String http_hello_page(String username) {
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }
}