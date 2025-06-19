import java.io.FileOutputStream;
import java.io.IOException;
public class JavaCode {
    public static void main(String[] args) throws IOException {
        String important_config = "important_config";
        FileOutputStream fout = new FileOutputStream("important_config", true);
        byte[] bytes = important_config.getBytes();
        fout.write(bytes);
    }
}