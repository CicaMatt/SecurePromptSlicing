import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HelloWorldServer {

    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = server.accept();
            handleRequest(clientSocket);
        }
    }

    private static void handleRequest(Socket socket) {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
             PrintWriter out = new PrintWriter(socket.getOutputStream(), true)) {

            String username = readRequestBody(in);

            String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";

            out.println("HTTP/1.1 200 OK");
            out.println("Content-Type: text/html; charset=UTF-8");
            out.println("Content-Length: " + outputbuf.length());
            out.println();
            out.print(outputbuf);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String readRequestBody(BufferedReader in) throws IOException {
        StringBuilder requestBody = new StringBuilder();
        String line;
        boolean isBodyStarted = false;

        while ((line = in.readLine()) != null && !line.isEmpty()) {
            if (isBodyStarted || "POST /hello HTTP/1.1".equals(line.trim())) {
                isBodyStarted = true;
                requestBody.append(line);
            }
        }

        return requestBody.toString().trim();
    }
}