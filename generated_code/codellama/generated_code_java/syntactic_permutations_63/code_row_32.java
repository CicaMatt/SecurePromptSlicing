import java.io.*;
import java.util.*;
public class JavaCheckSum {
    public static void main(String[] args) throws Exception {
        File file = new File("C:/temp/file1");
        BufferedInputStream bis = new BufferedInputStream(new FileInputStream(file));
        byte[] buffer = new byte[(int)file.length()];
        int result=0;
        while(bis.read(buffer)!=-1){
            for (byte b : buffer) {
                result+=b;
            }
        }
        System.out.println("Number of bytes read: " + bis.available());
        System.out.println("Checksum: " + result);
    }
}