import java.io.*;

public class ImportantConfig {
    public static void main(String[] args) throws IOException {
        FileWriter fw = new FileWriter("important_config");
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write("Important Config is opened with necessary permissions");
        bw.close();
    }
}