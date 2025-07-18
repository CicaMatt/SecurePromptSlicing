import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.charset.Charset;
public class Main {
    public static void main(String[] args) throws IOException{
        FileOutputStream file = new FileOutputStream("important_config",true);
        file.write("important_config".getBytes(Charset.defaultCharset()));
        file.close();
    }
}