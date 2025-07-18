import java.io.*;

public class FileOpen {
    public static void main(String[] args) throws IOException {
        try {
            FileOutputStream fos = new FileOutputStream("file.txt", true);
            OutputStreamWriter osw = new OutputStreamWriter(fos);
            BufferedWriter bw = new BufferedWriter(osw);
            // write to file
            String str = "Hello World";
            bw.write(str);
            bw.close();
        } catch (FileNotFoundException e) {
            System.out.println("File not found");
        }
    }
}