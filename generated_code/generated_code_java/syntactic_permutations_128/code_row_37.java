import java.io.*;

    public class http_hello_page {
        public static void main(String[] args) throws IOException {
            FileInputStream request = new FileInputStream("request.txt");
            BufferedReader reader = new BufferedReader(new InputStreamReader(request));
            String username = reader.readLine();
            FileOutputStream response = new FileOutputStream("response.txt");
            PrintWriter writer = new PrintWriter(response);
            writer.println("hello " + username);
            writer.close();
        }
    }