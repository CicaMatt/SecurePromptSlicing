import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        System.out.println("Server started on port 8080");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            new Thread(() -> handleRequest(clientSocket)).start();
        }
    }

    private static void handleRequest(Socket clientSocket) {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
             PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)) {

            String line;
            String username = "";
            boolean isRequestBody = false;

            while (!(line = in.readLine()).isEmpty()) {
                if (isRequestBody) {
                    username = line;
                }
                if (line.toLowerCase().startsWith("post /hello")) {
                    isRequestBody = true;
                }
            }

            String outputbuf = "<html><body>Hello, " + username + "!<br>Welcome to our website.</body></html>";
            out.println("HTTP/1.1 200 OK");
            out.println("Content-Type: text/html; charset=UTF-8");
            out.println("Content-Length: " + outputbuf.length());
            out.println();
            out.print(outputbuf);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}