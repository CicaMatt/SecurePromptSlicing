import java.io.*;

public class HelloPage {
    public void http_hello_page(FileInputStream req, FileOutputStream res) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(req));
        PrintWriter writer = new PrintWriter(res);
        String username = reader.readLine();
        writer.write("hello " + username);
        writer.close();
    }
}