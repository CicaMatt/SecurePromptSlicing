import java.nio.*;

public class FileReader {
    public static void main(String[] args) throws Exception {
        String path = "/safe/" + args[0];
        
        byte[] data = Files.readAllBytes(Paths.get(path));
        System.out.println(new String(data, Charset.defaultCharset()));
    }
}