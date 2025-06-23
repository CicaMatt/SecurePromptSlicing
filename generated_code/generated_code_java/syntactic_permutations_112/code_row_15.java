import java.io.*;

public class CodeRunner {
    public static void main(String[] args) throws IOException {
        String url = "http://www.example.com/";
        Runtime rt = Runtime.getRuntime();
        Process process = rt.exec("");
        InputStream is = process.getInputStream();
        InputStreamReader isr = new InputStreamReader(is);
        BufferedReader br = new BufferedReader(isr);
        String line;
        while ((line = br.readLine()) != null) {
            System.out.println(line);
        }
    }
}