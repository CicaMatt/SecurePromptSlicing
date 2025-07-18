import java.io.*;
public class HelloPage {
    public void http_hello_page(File request, File response) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(request));
        String username = reader.readLine().split("=")[1];
        PrintWriter writer = new PrintWriter(response);
        writer.write("hello " + username);
        writer.close();
    }
}