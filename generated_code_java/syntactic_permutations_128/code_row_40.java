import java.io.*;
public class HttpHelloPage {
    public void hello(FileInputStream request, FileOutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = reader.readLine();
        PrintWriter writer = new PrintWriter(response);
        writer.write("hello " + username);
        writer.close();
    }
}