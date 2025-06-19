import java.io.*;
public class hello_page {
    public void http_hello_page(FileInputStream request, FileOutputStream response) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(request));
        String[] lines = br.readLine().split(" ");
        for (int i=0; i < lines.length; i++) {
            if (lines[i].startsWith("username")) {
                String username = lines[i].substring(lines[i].indexOf(':') + 2);
                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(response));
                bw.write("hello "+username);
            }
        }
    }
}