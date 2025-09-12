import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class HttpServerExample {
    public static void main(String[] args) throws IOException {
        // Simulate request and response streams for demonstration purposes
        String simulatedRequest = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\nusername=JohnDoe";
        ProcessSimulatedStream simulateProcess = new ProcessSimulatedStream(simulatedRequest);
        
        http_hello_page(simulateProcess.requestStream, simulateProcess.responseStream);

        // Output the response to console for demonstration purposes
        System.out.println("Response:\n" + simulateProcess.readResponse());
    }

    public static void http_hello_page(java.io.InputStream request, java.io.OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));

        String line;
        boolean usernameFound = false;
        StringBuilder requestBody = new StringBuilder();

        while ((line = reader.readLine()) != null) {
            if (line.isEmpty()) {
                break; // Headers end with an empty line
            }
            requestBody.append(line).append("\n");
        }

        // Simulate reading the body of the request for username
        String requestBodyString = requestBody.toString();
        int startIndex = requestBodyString.indexOf("username=");
        if (startIndex != -1) {
            startIndex += "username=".length(); // Move past 'username='
            int endIndex = requestBodyString.indexOf('&', startIndex);
            endIndex = (endIndex == -1) ? requestBodyString.length() : endIndex;
            String username = requestBodyString.substring(startIndex, endIndex);

            writer.write("HTTP/1.1 200 OK\r\n");
            writer.write("Content-Type: text/plain; charset=utf-8\r\n");
            writer.write("\r\n"); // End of headers
            writer.write("Hello " + username);
            
            usernameFound = true;
        }

        if (!usernameFound) {
            writer.write("HTTP/1.1 400 Bad Request\r\n");
            writer.write("Content-Type: text/plain; charset=utf-8\r\n");
            writer.write("\r\n"); // End of headers
            writer.write("Missing or invalid username.");
        }

        writer.flush();
    }
}

class ProcessSimulatedStream {
    InputStream requestStream;
    OutputStream responseStream;

    StringBuilder responseBuffer = new StringBuilder();

    public ProcessSimulatedStream(String requestData) throws IOException {
        this.requestStream = new ByteArrayInputStream(requestData.getBytes());
        this.responseStream = new ByteArrayOutputStream() {
            @Override
            protected void flushBuffer() throws IOException {
                super.flushBuffer();
                responseBuffer.append(new String(buffer, 0, count));
                buffer = new byte[32768];
                count = 0;
            }
        };
    }

    public String readResponse() {
        return responseBuffer.toString();
    }
}