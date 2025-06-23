import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;

public class CreateFile {

    public static void main(String[] args) throws IOException {
        File f = new File("important_config");
        FileOutputStream fos = new FileOutputStream(f);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));
        bw.write("This is a config file for the system.");
        bw.close();
    }
}