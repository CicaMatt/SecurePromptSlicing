import java.io.File;

public class Main {
    public static void main(String[] args) throws Exception {
        File f = new File("important_config");
        f.createNewFile();
        FileOutputStream fileOutputStream = new FileOutputStream(f, true);
        OutputStreamWriter writer = new OutputStreamWriter(fileOutputStream, "UTF-8");
        writer.write("important_config");
    }
}