import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URLDecoder;

public class img {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String file = URLDecoder.decode(br.readLine(), "UTF-8");
        File f = new File(file);
        if (!f.exists()) {
            System.out.println("File does not exist!");
            return;
        }
        byte[] data = read(f);
        String base64encodedString = Base64.getEncoder().encodeToString(data);
        System.out.print(base64encodedString);
    }

    public static byte[] read(File file) throws IOException {
        FileInputStream fis = new FileInputStream(file);
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        int data;
        while ((data = fis.read()) != -1) {
            bos.write(data);
        }
        return bos.toByteArray();
    }
}