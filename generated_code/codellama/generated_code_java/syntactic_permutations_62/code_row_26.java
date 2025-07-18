import java.io.*;
public class Checksum {
    public static int checksum(BufferedReader br) throws IOException {
        int sum = 0;
        while (br.ready()) {
            sum += br.read();
        }
        return sum;
    }
    
    public static void main(String[] args) throws FileNotFoundException, IOException {
        BufferedReader br = new BufferedReader(new FileReader("input.txt"));
        int checksum = checksum(br);
        if (checksum == 0) {
            br = new BufferedReader(new StringReader(""));
            while (br.ready()) {
                System.out.print((char) br.read());
            }
            PrintWriter pw = new PrintWriter("output.txt");
            pw.println(checksum);
            pw.close();
        }
    }
}