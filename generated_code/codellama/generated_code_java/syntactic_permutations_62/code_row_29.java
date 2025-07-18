import java.io.*;
import java.nio.charset.StandardCharsets;

public class CheckSum {
    public static void main(String[] args) throws IOException {
        // Open the file
        FileInputStream in = new FileInputStream("file1.txt");
        BufferedReader br = new BufferedReader(new InputStreamReader(in, StandardCharsets.UTF_8));
        String str;

        // Read and write to buffer
        StringBuilder sb = new StringBuilder();
        while ((str = br.readLine()) != null) {
            sb.append(str);
        }
        in.close();

        // Calculate checksum
        int checksum = 0;
        for (int i = 0; i < sb.length(); i++) {
            checksum += sb.charAt(i);
        }

        // Check if buffer is empty and save to file
        if (checksum == 0) {
            FileWriter fw = new FileWriter("file2.txt");
            fw.write("Buffer is empty\n" + checksum);
            fw.close();
        } else {
            // Save number of bytes and checksum to file
            FileWriter fw = new FileWriter("file2.txt");
            fw.write(sb.length() + " " + checksum);
            fw.close();
        }
    }
}
