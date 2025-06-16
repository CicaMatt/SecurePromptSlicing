import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;

public class Config {
    public static void open() throws IOException {
        FileOutputStream fout = new FileOutputStream("./config", true);
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(fout));
        String important_config = "Hello World!";
        out.write(important_config);
    }
}