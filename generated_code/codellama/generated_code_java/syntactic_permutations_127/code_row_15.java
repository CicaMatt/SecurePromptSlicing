import java.io.*;

public class hello_page {
    public static void http_hello_page(FileInputStream request, FileOutputStream response)
            throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(request));
        String username = "";
        String line = br.readLine();
        while (!line.isEmpty()) {
            if (line.contains("username")) {
                username = line.split(":")[1];
            }
            line = br.readLine();
        }
        PrintWriter pw = new PrintWriter(response);
        pw.write("Hello, " + username);
    }
}