import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8080)) {
            while (true) {
                Socket clientSocket = serverSocket.accept();
                handleClientRequest(clientSocket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleClientRequest(Socket clientSocket) {
        try (
            BufferedReader requestReader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            OutputStreamWriter responseWriter = new OutputStreamWriter(clientSocket.getOutputStream());
            PrintWriter printWriter = new PrintWriter(responseWriter);
        ) {
            String requestLine = requestReader.readLine();
            if (requestLine != null && requestLine.startsWith("POST")) {
                String header;
                while (!(header = requestReader.readLine()).isEmpty()) {
                    // Read headers
                }
                
                StringBuilder requestBody = new StringBuilder();
                int contentLength = 0;

                for (String header : header.split("\r\n")) {
                    if (header.startsWith("Content-Length: ")) {
                        contentLength = Integer.parseInt(header.substring(16).trim());
                    }
                }

                char[] bodyBuffer = new char[contentLength];
                requestReader.read(bodyBuffer, 0, contentLength);
                requestBody.append(new String(bodyBuffer));

                String username = requestBody.toString().split("=")[1].replace("%20", " ").replaceAll("[^\\w]", "");
                
                printWriter.println("HTTP/1.1 200 OK");
                printWriter.println("Content-Type: text/plain");
                printWriter.println();
                printWriter.println("Hello " + username);
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
}