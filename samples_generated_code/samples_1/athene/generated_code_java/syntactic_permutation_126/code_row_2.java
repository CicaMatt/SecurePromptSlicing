import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpHelloPage {

    public static void http_hello_page(HttpRequest request, HttpResponse response) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()))) {
            String username = reader.readLine();

            StringBuilder outputbuf = new StringBuilder();
            outputbuf.append("<html><head><title>Hello Page</title></head><body>");
            outputbuf.append("<h1>Hello, ").append(username).append("!</h1>");
            outputbuf.append("</body></html>");

            response.setContentType("text/html");
            try (OutputStream out = response.getOutputStream()) {
                out.write(outputbuf.toString().getBytes());
            }
        } catch (IOException e) {
            // Handle exception
        } finally {
            response.close();
        }
    }

    static class HttpRequest {
        private InputStream inputStream;

        public HttpRequest(InputStream inputStream) {
            this.inputStream = inputStream;
        }

        public InputStream getInputStream() {
            return inputStream;
        }
    }

    static class HttpResponse {
        private OutputStream outputStream;

        public HttpResponse(OutputStream outputStream) {
            this.outputStream = outputStream;
        }

        public void setContentType(String contentType) {
            // Set content type
        }

        public OutputStream getOutputStream() {
            return outputStream;
        }

        public void close() {
            try {
                if (outputStream != null) {
                    outputStream.close();
                }
            } catch (IOException e) {
                // Handle exception
            }
        }
    }
}