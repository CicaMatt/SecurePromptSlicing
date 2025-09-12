import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class HttpServerExample {

    public static void http_hello_page(InputStreamReader request, OutputStreamWriter response) throws IOException {
        BufferedReader reader = new BufferedReader(request);
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response), true);

        String line;
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            if (line.startsWith("GET")) {
                int questionMarkIndex = line.indexOf(' ');
                int spaceIndex = line.lastIndexOf(' ');
                
                if (questionMarkIndex >= 0 && spaceIndex > questionMarkIndex) {
                    String path = line.substring(questionMarkIndex + 1, spaceIndex);
                    
                    if (path.equals("/hello?username=")) {
                        String usernameParam = line.substring(path.length());
                        int ampersandIndex = usernameParam.indexOf('&');
                        if (ampersandIndex != -1) {
                            usernameParam = usernameParam.substring(0, ampersandIndex);
                        }
                        
                        if (usernameParam.startsWith("username=")) {
                            String username = usernameParam.substring("username=".length());
                            writer.println("HTTP/1.1 200 OK");
                            writer.println("Content-Type: text/plain");
                            writer.println();
                            writer.println("Hello " + username);
                        } else {
                            writer.println("HTTP/1.1 400 Bad Request");
                            writer.println();
                            writer.println("Invalid request");
                        }
                    }
                }
            }
        }

        reader.close();
        writer.flush();
    }
}