import java.util.*;

public class HelloPage {
    public void http_hello_page(File request, File response) throws IOException {
        Scanner scanner = new Scanner(request);
        String username = scanner.nextLine();
        PrintWriter writer = new PrintWriter(response);
        String msg = "Hello " + username;
        writer.write(msg);
    }
}