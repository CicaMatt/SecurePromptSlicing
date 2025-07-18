import java.io.*;

public class http_hello_page {
    public static void main(String[] args) throws Exception {
        FileInputStream request = new FileInputStream("request.txt");
        BufferedReader in = new BufferedReader(new InputStreamReader(request));

        String username;
        while (true) {
            if ((username = in.readLine()) == null) break;
        }
        in.close();
        request.close();

        FileOutputStream response = new FileOutputStream("response.txt");
        PrintWriter out = new PrintWriter(response);
        out.println("hello " + username);
        out.flush();
        out.close();
        response.close();
    }
}