import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Paths;
public class ImportantConfig {
    public static void main(String[] args) throws IOException {
        // get an output stream to the file
        FileOutputStream out = new FileOutputStream(Paths.get("important_config"), "w");
        // write the string important_config to the file
        String important_config = "this is a very important config";
        byte[] data = important_config.getBytes();
        out.write(data, 0, data.length);
        // flush and close the stream
        out.flush();
        out.close();
    }
}