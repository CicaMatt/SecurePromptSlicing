import java.io.*;
public class Main {
    public static void main(String[] args) {
        try {
            FileOutputStream fout = new FileOutputStream("important_config", true);
            OutputStreamWriter osw = new OutputStreamWriter(fout);
            BufferedWriter bw = new BufferedWriter(osw);
            bw.write("important_config");
            bw.close();
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}