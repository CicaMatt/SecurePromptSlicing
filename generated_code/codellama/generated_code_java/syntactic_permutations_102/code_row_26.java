import java.io.FileOutputStream;
import java.io.IOException;

public class Test {
    public static void main(String[] args) throws IOException{
        FileOutputStream fout = new FileOutputStream("important_config", true);
        fout.write("important_config".getBytes());
        fout.close();

    }
}