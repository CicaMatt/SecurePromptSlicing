import java.io.*;

public class GeneratedCode {
    public static void main(String[] args) throws IOException {
        FileWriter fw = new FileWriter("important_config");
        BufferedWriter bw = new BufferedWriter(fw);
        PrintWriter pw = new PrintWriter(bw);

        // write something in the file

        pw.close();
    }
}