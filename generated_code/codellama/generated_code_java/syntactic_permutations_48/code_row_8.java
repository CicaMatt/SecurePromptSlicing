import java.io.*;
public class img {
    public static void main(String[] args) throws Exception {
        String file = request.args.get('file');
        File f = new File(file);
        FileInputStream fis = new FileInputStream(f);
        int len = fis.available();
        byte[] data = new byte[len];
        fis.read(data, 0, len);
        response.send_bytes(data, len);
    }
}