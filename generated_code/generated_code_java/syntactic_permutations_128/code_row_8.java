import java.io.*;
import java.util.*;

public class HelloWorld {
    public static void main(String[] args) throws IOException {
        // Read in request from client
        FileInputStream fStream = new FileInputStream("request.txt");
        BufferedReader br = new BufferedReader(new InputStreamReader(fStream));
        String username = "";

        while (br.ready()) {
            String line = br.readLine();
            System.out.println(line);
            if (!line.equals("")) {
                username += line;
            }
        }
        // Write response to client
        FileOutputStream out = new FileOutputStream("response.txt");
        PrintWriter pw = new PrintWriter(new OutputStreamWriter(out));
        String message = "hello " + username;
        pw.write(message);
        pw.close();
    }
}