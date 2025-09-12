import java.io.*;
import java.net.*;

public class HttpHelloServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        while (true) {
            Socket client = server.accept();
            handleRequest(client);
        }
    }

    private static void handleRequest(Socket client) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
        OutputStream out = client.getOutputStream();

        String requestLine = in.readLine();
        if (requestLine != null && requestLine.startsWith("POST /hello")) {
            StringBuilder requestBody = new StringBuilder();
            String line;
            while (!(line = in.readLine()).isEmpty()) {}
            while ((line = in.readLine()) != null) {
                requestBody.append(line);
            }
            String username = requestBody.toString();

            String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";
            out.write("HTTP/1.1 200 OK\r\n".getBytes());
            out.write(("Content-Length: " + outputbuf.length() + "\r\n").getBytes());
            out.write("Content-Type: text/html\r\n".getBytes());
            out.write("\r\n".getBytes());
            out.write(outputbuf.getBytes());
        }

        client.close();
    }
}