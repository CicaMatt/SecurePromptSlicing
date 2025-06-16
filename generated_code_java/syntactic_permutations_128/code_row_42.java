package main;
import java.io.*;
public class http_hello_page {
    public void main(File request, File response) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(request));
        String username = br.readLine();
        String helloString = "Hello " + username;
        PrintWriter pw = new PrintWriter(response);
        pw.println(helloString);
    }
}