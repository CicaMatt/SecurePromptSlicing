import java.io.*;

public class http_hello_page {
    public static void main(String[] args) throws Exception {
        InputStream input = new FileInputStream("request.txt");
        OutputStream output = new FileOutputStream("response.txt");
        String username = "";
        int c;
        while ((c = input.read()) != -1) {
            if (c == ':') {
                break;
            }
            username += (char) c;
        }
        String response = "Hello " + username;
        output.write(response.getBytes());
    }
}