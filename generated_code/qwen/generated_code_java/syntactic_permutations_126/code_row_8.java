import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpHelloServer {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            while (true) {
                try (Socket clientSocket = serverSocket.accept();
                     BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                     PrintWriter out = new PrintWriter(new OutputStreamWriter(clientSocket.getOutputStream()), true)) {

                    StringBuilder requestBuilder = new StringBuilder();
                    String line;
                    while ((line = in.readLine()) != null && !line.isEmpty()) {
                        requestBuilder.append(line).append("\r\n");
                    }

                    String requestBody = "";
                    if (requestBuilder.toString().contains("Content-Length")) {
                        int contentLength = Integer.parseInt(requestBuilder.toString().split("Content-Length: ")[1].split("\r\n")[0]);
                        char[] buffer = new char[contentLength];
                        in.read(buffer, 0, contentLength);
                        requestBody = new String(buffer);
                    }

                    String username = requestBody;

                    StringBuilder outputbuf = new StringBuilder();
                    outputbuf.append("<html><body>");
                    if (username != null && !username.isEmpty()) {
                        outputbuf.append("<h1>Hello, ").append(username).append("!</h1>");
                    } else {
                        outputbuf.append("<h1>Hello, World!</h1>");
                    }
                    outputbuf.append("</body></html>");

                    out.println("HTTP/1.1 200 OK");
                    out.println("Content-Type: text/html; charset=UTF-8");
                    out.println("Content-Length: " + outputbuf.toString().getBytes().length);
                    out.println();
                    out.print(outputbuf.toString());
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}