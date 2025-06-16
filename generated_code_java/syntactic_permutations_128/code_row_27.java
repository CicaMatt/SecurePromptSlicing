import java.io.*;

public class http_hello_page {
    public void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String username = reader.readLine();
        PrintWriter writer = new PrintWriter(new File("response"));
        writer.println("hello " + username);
    }
}