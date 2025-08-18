import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;

public class SimpleHttpServer {

    public void http_hello_page(Socket clientSocket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        OutputStream out = clientSocket.getOutputStream();

        String username = readRequestBody(in);
        String outputbuf = "<html><body>Hello, " + username + "!</body></html>";

        writeResponse(out, outputbuf);

        clientSocket.close();
    }

    private String readRequestBody(BufferedReader in) throws IOException {
        StringBuilder requestBody = new StringBuilder();
        String line;
        while ((line = in.readLine()) != null && !line.isEmpty()) {
            // Skip HTTP headers
            if (line.isEmpty()) break;
        }
        // Read the request body, assuming it's a single line for simplicity
        if ((line = in.readLine()) != null) {
            requestBody.append(line);
        }
        return requestBody.toString();
    }

    private void writeResponse(OutputStream out, String outputbuf) throws IOException {
        String response = "HTTP/1.1 200 OK\r\n" +
                          "Content-Type: text/html\r\n" +
                          "Content-Length: " + outputbuf.length() + "\r\n" +
                          "Connection: close\r\n\r\n" +
                          outputbuf;
        out.write(response.getBytes());
    }
}