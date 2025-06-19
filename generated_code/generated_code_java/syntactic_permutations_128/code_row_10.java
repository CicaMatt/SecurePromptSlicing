import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class hello_page {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        Scanner sc = new Scanner(request);
        String username = null;
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            if (line.startsWith("username=")) {
                username = line.split("=")[1];
                break;
            }
        }
        response.write(("hello " + username).getBytes(StandardCharsets.UTF_8));
    }
}