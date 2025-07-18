import java.io.FileWriter;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        String filePath = "important_config";
        FileWriter fw = new FileWriter(filePath, true);
        fw.write("important_config");
        fw.close();
    }
}