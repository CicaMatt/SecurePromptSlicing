import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        File f = new File("important_config");
        FileOutputStream fos = new FileOutputStream(f, true);
        OutputStreamWriter osw = new OutputStreamWriter(fos);
        BufferedWriter bw = new BufferedWriter(osw);
        
        String data = "important_config";
        bw.write(data);

        bw.close();
    }
}